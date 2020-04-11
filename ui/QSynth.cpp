#include <QDebug>

#include "QSynth.hpp"

QSynthDevice::QSynthDevice(Synth &synth, QMutex &mutex, QObject *parent) : QIODevice(parent), m_synth(synth), m_mutex(mutex) {
    setOpenMode(ReadOnly);
}

qint64 QSynthDevice::readData(char *data, qint64 maxSize) {
    QMutexLocker locker(&m_mutex);
    const qint64 sampleCount = maxSize / sizeof(float);
    float *samples = (float *)data;
    if (sampleCount > 0) {
        samples[0] = m_synth.update();
        m_synth.kbd.trigger = false;
        for (qint64 i = 1; i < sampleCount; ++i)
            samples[i] = m_synth.update();
    }
    return sampleCount * sizeof(float);
}

qint64 QSynthDevice::writeData(const char* data, qint64 maxSize) {
    return -1;
}

QSynth::QSynth(QObject *parent) : QSynthBase(parent),
                                  m_settings("./presets.ini", QSettings::IniFormat),
                                  m_midi(RtMidiIn::UNSPECIFIED, QCoreApplication::applicationName().toStdString()),
                                  m_device(m_synth, m_mutex, this) {
    initPreset();
    initMidiInput();
    initAudioOutput();
}

void QSynth::initPreset() {
    connect(this, &QSynth::controlChanged, [&]{
        this->m_presetDirty = true;
        emit this->presetDirtyChanged();
    });
    loadPreset(m_settings.childGroups().first());
}

void QSynth::initMidiInput() {
    const auto port = 1;
    qInfo() << m_midi.getPortName(port).c_str();
    m_midi.openPort(port);
    m_midi.setCallback([](double delta, std::vector<unsigned char> *message, void *userData) {
        auto& self = *static_cast<QSynth *>(userData);
        const auto type = (*message)[0];
        const auto note = (*message)[1];
        const float frequency = (440.f / 32.f) * std::pow(2.f, (note - 9.f) / 12.f);
        switch ((*message)[0]) {
            case 144: // note on
                {
                    self.m_mutex.lock();
                    self.m_synth.kbd.freq_target = frequency;
                    self.m_synth.kbd.trigger = true;
                    self.m_synth.kbd.gate = true;
                    self.m_mutex.unlock();
                    emit self.noteOn();
                }
                break;
            case 128: // note off
                {
                    self.m_mutex.lock();
                    if (frequency == self.m_synth.kbd.freq_target) {
                        self.m_synth.kbd.gate = false;
                        self.m_mutex.unlock();
                        emit self.noteOff();
                    } else {
                        self.m_mutex.unlock();
                    }
                }
                break;
        }
    }, this);
}

void QSynth::initAudioOutput() {
    QAudioFormat format;
    format.setCodec("audio/pcm");
    format.setChannelCount(1);
    format.setSampleRate(m_synth.sr);
    format.setSampleSize(sizeof(float) * 8);
    format.setSampleType(QAudioFormat::Float);
    m_output = new QAudioOutput(format, this);
    m_output->setBufferSize(m_synth.sr / 10 * sizeof(float));
    m_output->start(&m_device);
    qInfo() << m_output->metaObject()->className() << m_output->error();
    qInfo() << m_output->format();
}

void QSynth::loadPreset(const QString &name) {
    m_settings.beginGroup(name);
    const auto mo = metaObject()->superClass();
    for (auto i = mo->propertyOffset(); i < mo->propertyCount(); ++i) {
        auto property = mo->property(i);
        QVariant value = m_settings.value(property.name());
        property.write(this, value);
    }
    m_settings.endGroup();
    m_presetName = name;
    emit presetNameChanged();
    m_presetDirty = false;
    emit presetDirtyChanged();
}

void QSynth::savePreset(const QString &name) {
    m_settings.beginGroup(name);
    const auto mo = metaObject()->superClass();
    for (auto i = mo->propertyOffset(); i < mo->propertyCount(); ++i) {
        auto property = mo->property(i);
        QVariant value = property.read(this);
        m_settings.setValue(property.name(), value);
    }
    m_settings.endGroup();
    m_presetName = name;
    emit presetNameChanged();
    m_presetDirty = false;
    emit presetDirtyChanged();
}
