#include <QDebug>

#include "QSynth.hpp"

QSynthDevice::QSynthDevice(Synth &synth, QObject *parent) : QIODevice(parent), m_synth(synth) {
    setOpenMode(ReadOnly);
}

qint64 QSynthDevice::readData(char *data, qint64 maxSize) {
    QMutexLocker locker(&mutex);
    const qint64 sampleCount = maxSize / sizeof(float);
    float *samples = (float *)data;
    for (qint64 i = 0; i < sampleCount; ++i)
        samples[i] = m_synth.update();
    return sampleCount * sizeof(float);
}

qint64 QSynthDevice::writeData(const char* data, qint64 maxSize) {
    return -1;
}

QSynthBase::QSynthBase(QObject *parent) :
        QObject(parent),
        m_device(m_synth, this),
        midi(RtMidiIn::UNSPECIFIED, QCoreApplication::applicationName().toStdString()) {
    QAudioFormat format;
    format.setCodec("audio/pcm");
    format.setChannelCount(1);
    format.setSampleRate(m_synth.sr);
    format.setSampleSize(sizeof(float) * 8);
    format.setSampleType(QAudioFormat::Float);
    m_output = new QAudioOutput(format, this);
    m_output->start(&m_device);
    qInfo() << m_output->metaObject()->className() << m_output->error();
    qInfo() << m_output->format();

    const auto port = 1;
    qInfo() << midi.getPortName(port).c_str();
    midi.openPort(port);
    midi.setCallback([](double delta, std::vector<unsigned char> *message, void *userData) {
        auto& self = *static_cast<QSynthBase*>(userData);
        const auto type = (*message)[0];
        const auto note = (*message)[1];
        const float frequency = (440.f / 32.f) * std::pow(2.f, (note - 9.f) / 12.f);
        switch ((*message)[0]) {
            case 144: // note on
                self.m_synth.kbd.freq_target = frequency;
                self.m_synth.kbd.trigger = true;
                self.m_synth.kbd.gate = true;
                break;
            case 128: // note off
                if (frequency == self.m_synth.kbd.freq_target)
                    self.m_synth.kbd.gate = false;
                break;
        }
    }, this);
}

QSynthBase::~QSynthBase() {
    delete m_output;
    m_output = nullptr;
}

QSynth::QSynth(QObject *parent) : QSynthBase(parent), settings("./presets.ini", QSettings::IniFormat) {
    loadPreset("Bass");
}

void QSynth::loadPreset(const QString &name) {
    settings.beginGroup(name);
    for (auto i = metaObject()->propertyOffset(); i < metaObject()->propertyCount(); ++i) {
        auto property = metaObject()->property(i);
        QVariant value = settings.value(property.name());
        property.write(this, value);
    }
    settings.endGroup();
}

void QSynth::savePreset(const QString &name) {
    settings.beginGroup(name);
    for (auto i = metaObject()->propertyOffset(); i < metaObject()->propertyCount(); ++i) {
        auto property = metaObject()->property(i);
        QVariant value = property.read(this);
        settings.setValue(property.name(), value);
    }
    settings.endGroup();
}
