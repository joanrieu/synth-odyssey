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

QSynthBase::QSynthBase(QObject *parent) : QObject(parent), m_device(m_synth, this) {
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
}

QSynthBase::~QSynthBase() {
    delete m_output;
    m_output = nullptr;
}
