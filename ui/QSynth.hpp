#pragma once

#include <QCoreApplication>
#include <QAudioOutput>
#include <QMutex>
#include <QMetaProperty>
#include <QSettings>

#include "../vendor/rtmidi/RtMidi.h"

#include "../core/synth.hpp"

class QSynthBase : public QObject {
    Q_OBJECT

protected:
    Synth m_synth;
    QMutex m_mutex;

    Q_PROPERTY(float kbd_portamento READ get_kbd_portamento WRITE set_kbd_portamento NOTIFY controlChanged)
    float get_kbd_portamento() { return m_synth.kbd.portamento; }
    void set_kbd_portamento(float newValue) { m_mutex.lock(); m_synth.kbd.portamento = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float kbd_transpose READ get_kbd_transpose WRITE set_kbd_transpose NOTIFY controlChanged)
    float get_kbd_transpose() { return m_synth.kbd.transpose; }
    void set_kbd_transpose(float newValue) { m_mutex.lock(); m_synth.kbd.transpose = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vco1_tune READ get_vco1_tune WRITE set_vco1_tune NOTIFY controlChanged)
    float get_vco1_tune() { return m_synth.vco1.tune; }
    void set_vco1_tune(float newValue) { m_mutex.lock(); m_synth.vco1.tune = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vco1_detune READ get_vco1_detune WRITE set_vco1_detune NOTIFY controlChanged)
    float get_vco1_detune() { return m_synth.vco1.detune; }
    void set_vco1_detune(float newValue) { m_mutex.lock(); m_synth.vco1.detune = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vco2_tune READ get_vco2_tune WRITE set_vco2_tune NOTIFY controlChanged)
    float get_vco2_tune() { return m_synth.vco2.tune; }
    void set_vco2_tune(float newValue) { m_mutex.lock(); m_synth.vco2.tune = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vco2_detune READ get_vco2_detune WRITE set_vco2_detune NOTIFY controlChanged)
    float get_vco2_detune() { return m_synth.vco2.detune; }
    void set_vco2_detune(float newValue) { m_mutex.lock(); m_synth.vco2.detune = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float lfo_freq READ get_lfo_freq WRITE set_lfo_freq NOTIFY controlChanged)
    float get_lfo_freq() { return m_synth.lfo.freq; }
    void set_lfo_freq(float newValue) { m_mutex.lock(); m_synth.lfo.freq = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vcf_cutoff READ get_vcf_cutoff WRITE set_vcf_cutoff NOTIFY controlChanged)
    float get_vcf_cutoff() { return m_synth.vcf.cutoff; }
    void set_vcf_cutoff(float newValue) { m_mutex.lock(); m_synth.vcf.cutoff = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vcf_reso READ get_vcf_reso WRITE set_vcf_reso NOTIFY controlChanged)
    float get_vcf_reso() { return m_synth.vcf.reso; }
    void set_vcf_reso(float newValue) { m_mutex.lock(); m_synth.vcf.reso = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float hpf_cutoff READ get_hpf_cutoff WRITE set_hpf_cutoff NOTIFY controlChanged)
    float get_hpf_cutoff() { return m_synth.hpf.cutoff; }
    void set_hpf_cutoff(float newValue) { m_mutex.lock(); m_synth.hpf.cutoff = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vca_gain READ get_vca_gain WRITE set_vca_gain NOTIFY controlChanged)
    float get_vca_gain() { return m_synth.vca.gain; }
    void set_vca_gain(float newValue) { m_mutex.lock(); m_synth.vca.gain = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float ar_attack READ get_ar_attack WRITE set_ar_attack NOTIFY controlChanged)
    float get_ar_attack() { return m_synth.ar.attack; }
    void set_ar_attack(float newValue) { m_mutex.lock(); m_synth.ar.attack = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float ar_release READ get_ar_release WRITE set_ar_release NOTIFY controlChanged)
    float get_ar_release() { return m_synth.ar.release; }
    void set_ar_release(float newValue) { m_mutex.lock(); m_synth.ar.release = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vco1_fm1 READ get_vco1_fm1 WRITE set_vco1_fm1 NOTIFY controlChanged)
    float get_vco1_fm1() { return m_synth.vco1.fm1; }
    void set_vco1_fm1(float newValue) { m_mutex.lock(); m_synth.vco1.fm1 = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vco1_fm2 READ get_vco1_fm2 WRITE set_vco1_fm2 NOTIFY controlChanged)
    float get_vco1_fm2() { return m_synth.vco1.fm2; }
    void set_vco1_fm2(float newValue) { m_mutex.lock(); m_synth.vco1.fm2 = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vco1_pw READ get_vco1_pw WRITE set_vco1_pw NOTIFY controlChanged)
    float get_vco1_pw() { return m_synth.vco1.pw; }
    void set_vco1_pw(float newValue) { m_mutex.lock(); m_synth.vco1.pw = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vco1_pwm READ get_vco1_pwm WRITE set_vco1_pwm NOTIFY controlChanged)
    float get_vco1_pwm() { return m_synth.vco1.pwm; }
    void set_vco1_pwm(float newValue) { m_mutex.lock(); m_synth.vco1.pwm = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vco2_fm1 READ get_vco2_fm1 WRITE set_vco2_fm1 NOTIFY controlChanged)
    float get_vco2_fm1() { return m_synth.vco2.fm1; }
    void set_vco2_fm1(float newValue) { m_mutex.lock(); m_synth.vco2.fm1 = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vco2_fm2 READ get_vco2_fm2 WRITE set_vco2_fm2 NOTIFY controlChanged)
    float get_vco2_fm2() { return m_synth.vco2.fm2; }
    void set_vco2_fm2(float newValue) { m_mutex.lock(); m_synth.vco2.fm2 = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vco2_pw READ get_vco2_pw WRITE set_vco2_pw NOTIFY controlChanged)
    float get_vco2_pw() { return m_synth.vco2.pw; }
    void set_vco2_pw(float newValue) { m_mutex.lock(); m_synth.vco2.pw = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vco2_pwm READ get_vco2_pwm WRITE set_vco2_pwm NOTIFY controlChanged)
    float get_vco2_pwm() { return m_synth.vco2.pwm; }
    void set_vco2_pwm(float newValue) { m_mutex.lock(); m_synth.vco2.pwm = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float sh_vco1 READ get_sh_vco1 WRITE set_sh_vco1 NOTIFY controlChanged)
    float get_sh_vco1() { return m_synth.sh.vco1; }
    void set_sh_vco1(float newValue) { m_mutex.lock(); m_synth.sh.vco1 = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float sh_noise READ get_sh_noise WRITE set_sh_noise NOTIFY controlChanged)
    float get_sh_noise() { return m_synth.sh.noise; }
    void set_sh_noise(float newValue) { m_mutex.lock(); m_synth.sh.noise = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float sh_lag READ get_sh_lag WRITE set_sh_lag NOTIFY controlChanged)
    float get_sh_lag() { return m_synth.sh.lag; }
    void set_sh_lag(float newValue) { m_mutex.lock(); m_synth.sh.lag = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float mix_noise_ring READ get_mix_noise_ring WRITE set_mix_noise_ring NOTIFY controlChanged)
    float get_mix_noise_ring() { return m_synth.mix.noise_ring; }
    void set_mix_noise_ring(float newValue) { m_mutex.lock(); m_synth.mix.noise_ring = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float mix_vco1 READ get_mix_vco1 WRITE set_mix_vco1 NOTIFY controlChanged)
    float get_mix_vco1() { return m_synth.mix.vco1; }
    void set_mix_vco1(float newValue) { m_mutex.lock(); m_synth.mix.vco1 = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float mix_vco2 READ get_mix_vco2 WRITE set_mix_vco2 NOTIFY controlChanged)
    float get_mix_vco2() { return m_synth.mix.vco2; }
    void set_mix_vco2(float newValue) { m_mutex.lock(); m_synth.mix.vco2 = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vcf_mod1 READ get_vcf_mod1 WRITE set_vcf_mod1 NOTIFY controlChanged)
    float get_vcf_mod1() { return m_synth.vcf.mod1; }
    void set_vcf_mod1(float newValue) { m_mutex.lock(); m_synth.vcf.mod1 = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vcf_mod2 READ get_vcf_mod2 WRITE set_vcf_mod2 NOTIFY controlChanged)
    float get_vcf_mod2() { return m_synth.vcf.mod2; }
    void set_vcf_mod2(float newValue) { m_mutex.lock(); m_synth.vcf.mod2 = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vcf_env READ get_vcf_env WRITE set_vcf_env NOTIFY controlChanged)
    float get_vcf_env() { return m_synth.vcf.env; }
    void set_vcf_env(float newValue) { m_mutex.lock(); m_synth.vcf.env = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float vca_env READ get_vca_env WRITE set_vca_env NOTIFY controlChanged)
    float get_vca_env() { return m_synth.vca.env; }
    void set_vca_env(float newValue) { m_mutex.lock(); m_synth.vca.env = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float adsr_attack READ get_adsr_attack WRITE set_adsr_attack NOTIFY controlChanged)
    float get_adsr_attack() { return m_synth.adsr.attack; }
    void set_adsr_attack(float newValue) { m_mutex.lock(); m_synth.adsr.attack = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float adsr_decay READ get_adsr_decay WRITE set_adsr_decay NOTIFY controlChanged)
    float get_adsr_decay() { return m_synth.adsr.decay; }
    void set_adsr_decay(float newValue) { m_mutex.lock(); m_synth.adsr.decay = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float adsr_sustain READ get_adsr_sustain WRITE set_adsr_sustain NOTIFY controlChanged)
    float get_adsr_sustain() { return m_synth.adsr.sustain; }
    void set_adsr_sustain(float newValue) { m_mutex.lock(); m_synth.adsr.sustain = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(float adsr_release READ get_adsr_release WRITE set_adsr_release NOTIFY controlChanged)
    float get_adsr_release() { return m_synth.adsr.release; }
    void set_adsr_release(float newValue) { m_mutex.lock(); m_synth.adsr.release = newValue; m_mutex.unlock(); emit controlChanged(); }

    Q_PROPERTY(bool vco1_kbd READ get_vco1_kbd WRITE set_vco1_kbd NOTIFY controlChanged)
    bool get_vco1_kbd() { return m_synth.vco1.kbd; }
    void set_vco1_kbd(bool newValue) { m_mutex.lock(); m_synth.vco1.kbd = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool vco2_sync READ get_vco2_sync WRITE set_vco2_sync NOTIFY controlChanged)
    bool get_vco2_sync() { return m_synth.vco2.sync; }
    void set_vco2_sync(bool newValue) { m_mutex.lock(); m_synth.vco2.sync = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool noise_white READ get_noise_white WRITE set_noise_white NOTIFY controlChanged)
    bool get_noise_white() { return m_synth.noise.white; }
    void set_noise_white(bool newValue) { m_mutex.lock(); m_synth.noise.white = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool vco1_fm1_is_lfo_sine READ get_vco1_fm1_is_lfo_sine WRITE set_vco1_fm1_is_lfo_sine NOTIFY controlChanged)
    bool get_vco1_fm1_is_lfo_sine() { return m_synth.vco1.fm1_is_lfo_sine; }
    void set_vco1_fm1_is_lfo_sine(bool newValue) { m_mutex.lock(); m_synth.vco1.fm1_is_lfo_sine = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool vco1_fm2_is_sh_out READ get_vco1_fm2_is_sh_out WRITE set_vco1_fm2_is_sh_out NOTIFY controlChanged)
    bool get_vco1_fm2_is_sh_out() { return m_synth.vco1.fm2_is_sh_out; }
    void set_vco1_fm2_is_sh_out(bool newValue) { m_mutex.lock(); m_synth.vco1.fm2_is_sh_out = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool vco1_pwm_is_lfo READ get_vco1_pwm_is_lfo WRITE set_vco1_pwm_is_lfo NOTIFY controlChanged)
    bool get_vco1_pwm_is_lfo() { return m_synth.vco1.pwm_is_lfo; }
    void set_vco1_pwm_is_lfo(bool newValue) { m_mutex.lock(); m_synth.vco1.pwm_is_lfo = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool vco2_fm1_is_lfo_sine READ get_vco2_fm1_is_lfo_sine WRITE set_vco2_fm1_is_lfo_sine NOTIFY controlChanged)
    bool get_vco2_fm1_is_lfo_sine() { return m_synth.vco2.fm1_is_lfo_sine; }
    void set_vco2_fm1_is_lfo_sine(bool newValue) { m_mutex.lock(); m_synth.vco2.fm1_is_lfo_sine = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool vco2_fm2_is_sh_out READ get_vco2_fm2_is_sh_out WRITE set_vco2_fm2_is_sh_out NOTIFY controlChanged)
    bool get_vco2_fm2_is_sh_out() { return m_synth.vco2.fm2_is_sh_out; }
    void set_vco2_fm2_is_sh_out(bool newValue) { m_mutex.lock(); m_synth.vco2.fm2_is_sh_out = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool vco2_pwm_is_lfo READ get_vco2_pwm_is_lfo WRITE set_vco2_pwm_is_lfo NOTIFY controlChanged)
    bool get_vco2_pwm_is_lfo() { return m_synth.vco2.pwm_is_lfo; }
    void set_vco2_pwm_is_lfo(bool newValue) { m_mutex.lock(); m_synth.vco2.pwm_is_lfo = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool sh_vco1_saw READ get_sh_vco1_saw WRITE set_sh_vco1_saw NOTIFY controlChanged)
    bool get_sh_vco1_saw() { return m_synth.sh.vco1_saw; }
    void set_sh_vco1_saw(bool newValue) { m_mutex.lock(); m_synth.sh.vco1_saw = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool sh_noise_gen READ get_sh_noise_gen WRITE set_sh_noise_gen NOTIFY controlChanged)
    bool get_sh_noise_gen() { return m_synth.sh.noise_gen; }
    void set_sh_noise_gen(bool newValue) { m_mutex.lock(); m_synth.sh.noise_gen = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool sh_lfo_trigger READ get_sh_lfo_trigger WRITE set_sh_lfo_trigger NOTIFY controlChanged)
    bool get_sh_lfo_trigger() { return m_synth.sh.lfo_trigger; }
    void set_sh_lfo_trigger(bool newValue) { m_mutex.lock(); m_synth.sh.lfo_trigger = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool mix_noise READ get_mix_noise WRITE set_mix_noise NOTIFY controlChanged)
    bool get_mix_noise() { return m_synth.mix.noise; }
    void set_mix_noise(bool newValue) { m_mutex.lock(); m_synth.mix.noise = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool mix_vco1_saw READ get_mix_vco1_saw WRITE set_mix_vco1_saw NOTIFY controlChanged)
    bool get_mix_vco1_saw() { return m_synth.mix.vco1_saw; }
    void set_mix_vco1_saw(bool newValue) { m_mutex.lock(); m_synth.mix.vco1_saw = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool mix_vco2_saw READ get_mix_vco2_saw WRITE set_mix_vco2_saw NOTIFY controlChanged)
    bool get_mix_vco2_saw() { return m_synth.mix.vco2_saw; }
    void set_mix_vco2_saw(bool newValue) { m_mutex.lock(); m_synth.mix.vco2_saw = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool vcf_mod1_kbd READ get_vcf_mod1_kbd WRITE set_vcf_mod1_kbd NOTIFY controlChanged)
    bool get_vcf_mod1_kbd() { return m_synth.vcf.mod1_kbd; }
    void set_vcf_mod1_kbd(bool newValue) { m_mutex.lock(); m_synth.vcf.mod1_kbd = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool vcf_mod2_sh READ get_vcf_mod2_sh WRITE set_vcf_mod2_sh NOTIFY controlChanged)
    bool get_vcf_mod2_sh() { return m_synth.vcf.mod2_sh; }
    void set_vcf_mod2_sh(bool newValue) { m_mutex.lock(); m_synth.vcf.mod2_sh = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool vcf_env_adsr READ get_vcf_env_adsr WRITE set_vcf_env_adsr NOTIFY controlChanged)
    bool get_vcf_env_adsr() { return m_synth.vcf.env_adsr; }
    void set_vcf_env_adsr(bool newValue) { m_mutex.lock(); m_synth.vcf.env_adsr = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool vca_env_ar READ get_vca_env_ar WRITE set_vca_env_ar NOTIFY controlChanged)
    bool get_vca_env_ar() { return m_synth.vca.env_ar; }
    void set_vca_env_ar(bool newValue) { m_mutex.lock(); m_synth.vca.env_ar = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool adsr_kbd_trigger READ get_adsr_kbd_trigger WRITE set_adsr_kbd_trigger NOTIFY controlChanged)
    bool get_adsr_kbd_trigger() { return m_synth.adsr.kbd_trigger; }
    void set_adsr_kbd_trigger(bool newValue) { m_mutex.lock(); m_synth.adsr.kbd_trigger = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool adsr_kbd_repeat READ get_adsr_kbd_repeat WRITE set_adsr_kbd_repeat NOTIFY controlChanged)
    bool get_adsr_kbd_repeat() { return m_synth.adsr.kbd_repeat; }
    void set_adsr_kbd_repeat(bool newValue) { m_mutex.lock(); m_synth.adsr.kbd_repeat = newValue; m_mutex.unlock(); emit controlChanged(); }
    Q_PROPERTY(bool ar_kbd_trigger READ get_ar_kbd_trigger WRITE set_ar_kbd_trigger NOTIFY controlChanged)
    bool get_ar_kbd_trigger() { return m_synth.ar.kbd_trigger; }
    void set_ar_kbd_trigger(bool newValue) { m_mutex.lock(); m_synth.ar.kbd_trigger = newValue; m_mutex.unlock(); emit controlChanged(); }

public:
    QSynthBase(QObject *parent) : QObject(parent) {}

signals:
    void controlChanged();
    void noteOn();
    void noteOff();
};

class QSynthDevice : public QIODevice {
    Q_OBJECT

    Synth &m_synth;
    QMutex &m_mutex;

public:
    QSynthDevice(Synth &synth, QMutex &mutex, QObject *parent);

protected:
    virtual qint64 readData(char *data, qint64 maxSize);
    virtual qint64 writeData(const char* data, qint64 maxSize);
};

class QSynth : public QSynthBase {
    Q_OBJECT

protected:
    QSettings settings;

    RtMidiIn midi;

    QSynthDevice m_device;
    QAudioOutput *m_output;

    QString m_presetName;
    Q_PROPERTY(QString presetName MEMBER m_presetName NOTIFY presetNameChanged)
    bool m_presetDirty;
    Q_PROPERTY(bool presetDirty MEMBER m_presetDirty NOTIFY presetDirtyChanged)

public:
    QSynth(QObject *parent);

    Q_INVOKABLE void loadPreset(const QString &name);
    Q_INVOKABLE void savePreset(const QString &name);

signals:
    void presetNameChanged();
    void presetDirtyChanged();
};
