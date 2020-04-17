#pragma once

#include <QCoreApplication>
#include <QAudioOutput>
#include <QMutex>
#include <QMetaProperty>
#include <QSettings>

#include "../vendor/rtmidi/RtMidi.h"

#include "../core/synth.hpp"

#define SYNTH_CONTROL(type, category, name) \
    Q_PROPERTY(type category ## _ ## name READ get_ ## category ## _ ## name WRITE set_ ## category ## _ ## name NOTIFY controlChanged) \
    type get_ ## category ## _ ## name () { \
        return m_synth[0].category.name; \
    } \
    void set_ ## category ## _ ## name (type newValue) { \
        m_mutex.lock(); \
        m_synth[0].category.name = newValue; \
        m_synth[1].category.name = newValue; \
        m_mutex.unlock(); \
        emit controlChanged(); \
    }

class QSynthBase : public QObject {
    Q_OBJECT

protected:
    Synth m_synth[2];
    QMutex m_mutex;

    SYNTH_CONTROL(float, kbd, portamento)
    SYNTH_CONTROL(float, kbd, transpose)
    SYNTH_CONTROL(float, vco1, tune)
    SYNTH_CONTROL(float, vco1, detune)
    SYNTH_CONTROL(float, vco2, tune)
    SYNTH_CONTROL(float, vco2, detune)
    SYNTH_CONTROL(float, lfo, freq)
    SYNTH_CONTROL(float, vcf, cutoff)
    SYNTH_CONTROL(float, vcf, reso)
    SYNTH_CONTROL(float, hpf, cutoff)
    SYNTH_CONTROL(float, vca, gain)
    SYNTH_CONTROL(float, ar, attack)
    SYNTH_CONTROL(float, ar, release)
    SYNTH_CONTROL(float, vco1, fm1)
    SYNTH_CONTROL(float, vco1, fm2)
    SYNTH_CONTROL(float, vco1, pw)
    SYNTH_CONTROL(float, vco1, pwm)
    SYNTH_CONTROL(float, vco2, fm1)
    SYNTH_CONTROL(float, vco2, fm2)
    SYNTH_CONTROL(float, vco2, pw)
    SYNTH_CONTROL(float, vco2, pwm)
    SYNTH_CONTROL(float, sh, vco1)
    SYNTH_CONTROL(float, sh, noise)
    SYNTH_CONTROL(float, sh, lag)
    SYNTH_CONTROL(float, mix, noise_ring)
    SYNTH_CONTROL(float, mix, vco1)
    SYNTH_CONTROL(float, mix, vco2)
    SYNTH_CONTROL(float, vcf, mod1)
    SYNTH_CONTROL(float, vcf, mod2)
    SYNTH_CONTROL(float, vcf, env)
    SYNTH_CONTROL(float, vca, env)
    SYNTH_CONTROL(float, adsr, attack)
    SYNTH_CONTROL(float, adsr, decay)
    SYNTH_CONTROL(float, adsr, sustain)
    SYNTH_CONTROL(float, adsr, release)

    SYNTH_CONTROL(bool, vco1, kbd)
    SYNTH_CONTROL(bool, vco2, sync)
    SYNTH_CONTROL(bool, noise, white)
    SYNTH_CONTROL(bool, vco1, fm1_is_lfo_sine)
    SYNTH_CONTROL(bool, vco1, fm2_is_sh_out)
    SYNTH_CONTROL(bool, vco1, pwm_is_lfo)
    SYNTH_CONTROL(bool, vco2, fm1_is_lfo_sine)
    SYNTH_CONTROL(bool, vco2, fm2_is_sh_out)
    SYNTH_CONTROL(bool, vco2, pwm_is_lfo)
    SYNTH_CONTROL(bool, sh, vco1_saw)
    SYNTH_CONTROL(bool, sh, noise_gen)
    SYNTH_CONTROL(bool, sh, lfo_trigger)
    SYNTH_CONTROL(bool, mix, noise)
    SYNTH_CONTROL(bool, mix, vco1_saw)
    SYNTH_CONTROL(bool, mix, vco2_saw)
    SYNTH_CONTROL(bool, vcf, mod1_kbd)
    SYNTH_CONTROL(bool, vcf, mod2_sh)
    SYNTH_CONTROL(bool, vcf, env_adsr)
    SYNTH_CONTROL(bool, vca, env_ar)
    SYNTH_CONTROL(bool, adsr, kbd_trigger)
    SYNTH_CONTROL(bool, adsr, kbd_repeat)
    SYNTH_CONTROL(bool, ar, kbd_trigger)

public:
    QSynthBase(QObject *parent) : QObject(parent) {}

signals:
    void controlChanged();
    void noteOn();
    void noteOff();
};

class QSynthDevice : public QIODevice {
    Q_OBJECT

    Synth *m_synth;
    QMutex &m_mutex;
    quint64 m_skip;

public:
    QSynthDevice(Synth synth[2], QMutex &mutex, QObject *parent);

protected:
    virtual qint64 readData(char *data, qint64 maxSize);
    virtual qint64 writeData(const char* data, qint64 maxSize);
};

class QSynth : public QSynthBase {
    Q_OBJECT

protected:
    QSettings m_settings;

    RtMidiIn m_midi;
    Q_PROPERTY(QStringList midiPorts READ midiPorts)
    QStringList midiPorts();
    Q_PROPERTY(int midiPort MEMBER m_midiPort WRITE setMidiPort NOTIFY midiPortChanged)
    int m_midiPort;
    void setMidiPort(int port);

    QSynthDevice m_device;
    QAudioOutput *m_output;

    Q_PROPERTY(QStringList presetNames READ presetNames NOTIFY presetNamesChanged)
    QStringList presetNames();
    Q_PROPERTY(QString presetName MEMBER m_presetName NOTIFY presetNameChanged)
    QString m_presetName;
    Q_PROPERTY(bool presetDirty MEMBER m_presetDirty NOTIFY presetDirtyChanged)
    bool m_presetDirty;

    void initPreset();
    void initAudioOutput();

public:
    QSynth(QObject *parent);

    Q_INVOKABLE void loadPreset(const QString &name);
    Q_INVOKABLE void savePreset(const QString &name);

signals:
    void presetNamesChanged();
    void presetNameChanged();
    void presetDirtyChanged();
    void midiPortChanged();
};
