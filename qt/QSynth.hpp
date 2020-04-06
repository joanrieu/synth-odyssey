#pragma once

#include <QAudioOutput>

#include "../core/control.hpp"

class QSynthDevice : public QIODevice {
    Q_OBJECT

    Synth &m_synth;

public:
    QSynthDevice(Synth &synth, QObject *parent);

protected:
    virtual qint64 readData(char *data, qint64 maxSize);
    virtual qint64 writeData(const char* data, qint64 maxSize);
};

class QSynth : public QObject {
    Q_OBJECT

    ControlledSynth m_synth;
    QSynthDevice m_device;
    QAudioOutput *m_output;

public:
    QSynth(QObject *parent);
    virtual ~QSynth();

    Q_INVOKABLE void setFloatControl(int index, float newValue);
    Q_INVOKABLE void setBooleanControl(int index, bool newValue);

signals:
    void floatControlChanged(int index, float newValue);
    void booleanControlChanged(int index, bool newValue);
};
