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
                                  m_midiPort(-1),
                                  m_device(m_synth, m_mutex, this) {
    initPreset();
    setMidiPort(m_midi.getPortCount() - 1);
    initAudioOutput();
}

void QSynth::initPreset() {
    connect(this, &QSynth::controlChanged, [&]{
        this->m_presetDirty = true;
        emit this->presetDirtyChanged();
    });
    loadPreset(m_settings.childGroups().first());
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

QStringList QSynth::midiPorts() {
    QStringList list;
    const unsigned count = m_midi.getPortCount();
    for (unsigned i = 0; i < count; ++i)
        list << QString::fromStdString(m_midi.getPortName(i));
    return list;
}

void QSynth::setMidiPort(int port) {
    if (m_midiPort >= 0) {
        m_midi.cancelCallback();
        m_midi.closePort();
        m_midiPort = -1;
        emit midiPortChanged();
    }
    if (port >= 0) {
        m_midi.openPort(port);
        m_midi.setCallback([](double delta, std::vector<unsigned char> *message, void *userData) {
            auto& self = *static_cast<QSynth *>(userData);
            const auto& status = (*message)[0];
            const auto& data1 = (*message)[1];
            const auto& data2 = (*message)[2];
            switch ((*message)[0]) {
                case 0x90: // note on
                    {
                        const float frequency = (440.f / 32.f) * std::pow(2.f, (data1 - 9.f) / 12.f);
                        self.m_mutex.lock();
                        self.m_synth.kbd.freq_target = frequency;
                        self.m_synth.kbd.trigger = true;
                        self.m_synth.kbd.gate = true;
                        self.m_mutex.unlock();
                        emit self.noteOn();
                    }
                    break;
                case 0x80: // note off
                    {
                        const float frequency = (440.f / 32.f) * std::pow(2.f, (data1 - 9.f) / 12.f);
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
                case 0xB0:
                    {
                        self.m_mutex.lock();
                        self.m_synth.vcf.cutoff = std::pow(data2 / 127.f, 2) * 16000;
                        self.m_mutex.unlock();
                        emit self.controlChanged();
                    }
                    break;
                case 0xE0:
                    {
                        self.m_mutex.lock();
                        const float value = ((int(data2) << 7) + int(data1)) / float(0b11111111111111) - 0.5;
                        const int sign = value >= 0 ? 1 : -1;
                        self.m_synth.kbd.pitch_bend = sign * std::pow(sign * value, 2);
                        self.m_mutex.unlock();
                    }
                    break;
            }
        }, this);
        m_midiPort = port;
        emit midiPortChanged();
    }
}

QStringList QSynth::presetNames() {
    return m_settings.childGroups();
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
    emit presetNamesChanged();
    m_presetName = name;
    emit presetNameChanged();
    m_presetDirty = false;
    emit presetDirtyChanged();
}
