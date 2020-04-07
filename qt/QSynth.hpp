#pragma once

#include <QAudioOutput>
#include <QMutexLocker>
#include <QMetaProperty>
#include <QSettings>

#include "../core/synth.hpp"

class QSynthDevice : public QIODevice {
    Q_OBJECT

    Synth &m_synth;

public:
    QSynthDevice(Synth &synth, QObject *parent);
    QMutex mutex;

protected:
    virtual qint64 readData(char *data, qint64 maxSize);
    virtual qint64 writeData(const char* data, qint64 maxSize);
};

class QSynthBase : public QObject {
    Q_OBJECT

protected:
    Synth m_synth;
    QSynthDevice m_device;
    QAudioOutput *m_output;
    std::vector<float *> m_floats;
    std::vector<bool *> m_booleans;

public:
    QSynthBase(QObject *parent);
    virtual ~QSynthBase();

signals:
    void controlChanged();
};

class QSynth : public QSynthBase {
    Q_OBJECT

    Q_PROPERTY(float kbd_portamento READ get_kbd_portamento WRITE set_kbd_portamento NOTIFY controlChanged)
    float get_kbd_portamento() { return m_synth.kbd.portamento; }
    void set_kbd_portamento(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.kbd.portamento = newValue; controlChanged(); }
    Q_PROPERTY(float kbd_transpose READ get_kbd_transpose WRITE set_kbd_transpose NOTIFY controlChanged)
    float get_kbd_transpose() { return m_synth.kbd.transpose; }
    void set_kbd_transpose(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.kbd.transpose = newValue; controlChanged(); }
    Q_PROPERTY(float vco1_tune READ get_vco1_tune WRITE set_vco1_tune NOTIFY controlChanged)
    float get_vco1_tune() { return m_synth.vco1.tune; }
    void set_vco1_tune(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco1.tune = newValue; controlChanged(); }
    Q_PROPERTY(float vco1_detune READ get_vco1_detune WRITE set_vco1_detune NOTIFY controlChanged)
    float get_vco1_detune() { return m_synth.vco1.detune; }
    void set_vco1_detune(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco1.detune = newValue; controlChanged(); }
    Q_PROPERTY(float vco2_tune READ get_vco2_tune WRITE set_vco2_tune NOTIFY controlChanged)
    float get_vco2_tune() { return m_synth.vco2.tune; }
    void set_vco2_tune(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco2.tune = newValue; controlChanged(); }
    Q_PROPERTY(float vco2_detune READ get_vco2_detune WRITE set_vco2_detune NOTIFY controlChanged)
    float get_vco2_detune() { return m_synth.vco2.detune; }
    void set_vco2_detune(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco2.detune = newValue; controlChanged(); }
    Q_PROPERTY(float lfo_freq READ get_lfo_freq WRITE set_lfo_freq NOTIFY controlChanged)
    float get_lfo_freq() { return m_synth.lfo.freq; }
    void set_lfo_freq(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.lfo.freq = newValue; controlChanged(); }
    Q_PROPERTY(float vcf_cutoff READ get_vcf_cutoff WRITE set_vcf_cutoff NOTIFY controlChanged)
    float get_vcf_cutoff() { return m_synth.vcf.cutoff; }
    void set_vcf_cutoff(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vcf.cutoff = newValue; controlChanged(); }
    Q_PROPERTY(float vcf_reso READ get_vcf_reso WRITE set_vcf_reso NOTIFY controlChanged)
    float get_vcf_reso() { return m_synth.vcf.reso; }
    void set_vcf_reso(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vcf.reso = newValue; controlChanged(); }
    Q_PROPERTY(float hpf_cutoff READ get_hpf_cutoff WRITE set_hpf_cutoff NOTIFY controlChanged)
    float get_hpf_cutoff() { return m_synth.hpf.cutoff; }
    void set_hpf_cutoff(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.hpf.cutoff = newValue; controlChanged(); }
    Q_PROPERTY(float vca_gain READ get_vca_gain WRITE set_vca_gain NOTIFY controlChanged)
    float get_vca_gain() { return m_synth.vca.gain; }
    void set_vca_gain(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vca.gain = newValue; controlChanged(); }
    Q_PROPERTY(float ar_attack READ get_ar_attack WRITE set_ar_attack NOTIFY controlChanged)
    float get_ar_attack() { return m_synth.ar.attack; }
    void set_ar_attack(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.ar.attack = newValue; controlChanged(); }
    Q_PROPERTY(float ar_release READ get_ar_release WRITE set_ar_release NOTIFY controlChanged)
    float get_ar_release() { return m_synth.ar.release; }
    void set_ar_release(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.ar.release = newValue; controlChanged(); }
    Q_PROPERTY(float vco1_fm1 READ get_vco1_fm1 WRITE set_vco1_fm1 NOTIFY controlChanged)
    float get_vco1_fm1() { return m_synth.vco1.fm1; }
    void set_vco1_fm1(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco1.fm1 = newValue; controlChanged(); }
    Q_PROPERTY(float vco1_fm2 READ get_vco1_fm2 WRITE set_vco1_fm2 NOTIFY controlChanged)
    float get_vco1_fm2() { return m_synth.vco1.fm2; }
    void set_vco1_fm2(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco1.fm2 = newValue; controlChanged(); }
    Q_PROPERTY(float vco1_pw READ get_vco1_pw WRITE set_vco1_pw NOTIFY controlChanged)
    float get_vco1_pw() { return m_synth.vco1.pw; }
    void set_vco1_pw(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco1.pw = newValue; controlChanged(); }
    Q_PROPERTY(float vco1_pwm READ get_vco1_pwm WRITE set_vco1_pwm NOTIFY controlChanged)
    float get_vco1_pwm() { return m_synth.vco1.pwm; }
    void set_vco1_pwm(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco1.pwm = newValue; controlChanged(); }
    Q_PROPERTY(float vco2_fm1 READ get_vco2_fm1 WRITE set_vco2_fm1 NOTIFY controlChanged)
    float get_vco2_fm1() { return m_synth.vco2.fm1; }
    void set_vco2_fm1(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco2.fm1 = newValue; controlChanged(); }
    Q_PROPERTY(float vco2_fm2 READ get_vco2_fm2 WRITE set_vco2_fm2 NOTIFY controlChanged)
    float get_vco2_fm2() { return m_synth.vco2.fm2; }
    void set_vco2_fm2(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco2.fm2 = newValue; controlChanged(); }
    Q_PROPERTY(float vco2_pw READ get_vco2_pw WRITE set_vco2_pw NOTIFY controlChanged)
    float get_vco2_pw() { return m_synth.vco2.pw; }
    void set_vco2_pw(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco2.pw = newValue; controlChanged(); }
    Q_PROPERTY(float vco2_pwm READ get_vco2_pwm WRITE set_vco2_pwm NOTIFY controlChanged)
    float get_vco2_pwm() { return m_synth.vco2.pwm; }
    void set_vco2_pwm(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco2.pwm = newValue; controlChanged(); }
    Q_PROPERTY(float sh_vco1 READ get_sh_vco1 WRITE set_sh_vco1 NOTIFY controlChanged)
    float get_sh_vco1() { return m_synth.sh.vco1; }
    void set_sh_vco1(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.sh.vco1 = newValue; controlChanged(); }
    Q_PROPERTY(float sh_noise READ get_sh_noise WRITE set_sh_noise NOTIFY controlChanged)
    float get_sh_noise() { return m_synth.sh.noise; }
    void set_sh_noise(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.sh.noise = newValue; controlChanged(); }
    Q_PROPERTY(float sh_lag READ get_sh_lag WRITE set_sh_lag NOTIFY controlChanged)
    float get_sh_lag() { return m_synth.sh.lag; }
    void set_sh_lag(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.sh.lag = newValue; controlChanged(); }
    Q_PROPERTY(float mix_noise_ring READ get_mix_noise_ring WRITE set_mix_noise_ring NOTIFY controlChanged)
    float get_mix_noise_ring() { return m_synth.mix.noise_ring; }
    void set_mix_noise_ring(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.mix.noise_ring = newValue; controlChanged(); }
    Q_PROPERTY(float mix_vco1 READ get_mix_vco1 WRITE set_mix_vco1 NOTIFY controlChanged)
    float get_mix_vco1() { return m_synth.mix.vco1; }
    void set_mix_vco1(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.mix.vco1 = newValue; controlChanged(); }
    Q_PROPERTY(float mix_vco2 READ get_mix_vco2 WRITE set_mix_vco2 NOTIFY controlChanged)
    float get_mix_vco2() { return m_synth.mix.vco2; }
    void set_mix_vco2(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.mix.vco2 = newValue; controlChanged(); }
    Q_PROPERTY(float vcf_mod1 READ get_vcf_mod1 WRITE set_vcf_mod1 NOTIFY controlChanged)
    float get_vcf_mod1() { return m_synth.vcf.mod1; }
    void set_vcf_mod1(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vcf.mod1 = newValue; controlChanged(); }
    Q_PROPERTY(float vcf_mod2 READ get_vcf_mod2 WRITE set_vcf_mod2 NOTIFY controlChanged)
    float get_vcf_mod2() { return m_synth.vcf.mod2; }
    void set_vcf_mod2(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vcf.mod2 = newValue; controlChanged(); }
    Q_PROPERTY(float vcf_env READ get_vcf_env WRITE set_vcf_env NOTIFY controlChanged)
    float get_vcf_env() { return m_synth.vcf.env; }
    void set_vcf_env(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vcf.env = newValue; controlChanged(); }
    Q_PROPERTY(float vca_env READ get_vca_env WRITE set_vca_env NOTIFY controlChanged)
    float get_vca_env() { return m_synth.vca.env; }
    void set_vca_env(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vca.env = newValue; controlChanged(); }
    Q_PROPERTY(float adsr_attack READ get_adsr_attack WRITE set_adsr_attack NOTIFY controlChanged)
    float get_adsr_attack() { return m_synth.adsr.attack; }
    void set_adsr_attack(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.adsr.attack = newValue; controlChanged(); }
    Q_PROPERTY(float adsr_decay READ get_adsr_decay WRITE set_adsr_decay NOTIFY controlChanged)
    float get_adsr_decay() { return m_synth.adsr.decay; }
    void set_adsr_decay(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.adsr.decay = newValue; controlChanged(); }
    Q_PROPERTY(float adsr_sustain READ get_adsr_sustain WRITE set_adsr_sustain NOTIFY controlChanged)
    float get_adsr_sustain() { return m_synth.adsr.sustain; }
    void set_adsr_sustain(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.adsr.sustain = newValue; controlChanged(); }
    Q_PROPERTY(float adsr_release READ get_adsr_release WRITE set_adsr_release NOTIFY controlChanged)
    float get_adsr_release() { return m_synth.adsr.release; }
    void set_adsr_release(float newValue) { QMutexLocker locker(&m_device.mutex); m_synth.adsr.release = newValue; controlChanged(); }

    Q_PROPERTY(bool kbd_sequencer READ get_kbd_sequencer WRITE set_kbd_sequencer NOTIFY controlChanged)
    bool get_kbd_sequencer() { return m_synth.kbd.sequencer; }
    void set_kbd_sequencer(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.kbd.sequencer = newValue; controlChanged(); }
    Q_PROPERTY(bool vco1_kbd READ get_vco1_kbd WRITE set_vco1_kbd NOTIFY controlChanged)
    bool get_vco1_kbd() { return m_synth.vco1.kbd; }
    void set_vco1_kbd(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco1.kbd = newValue; controlChanged(); }
    Q_PROPERTY(bool vco2_sync READ get_vco2_sync WRITE set_vco2_sync NOTIFY controlChanged)
    bool get_vco2_sync() { return m_synth.vco2.sync; }
    void set_vco2_sync(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco2.sync = newValue; controlChanged(); }
    Q_PROPERTY(bool noise_white READ get_noise_white WRITE set_noise_white NOTIFY controlChanged)
    bool get_noise_white() { return m_synth.noise.white; }
    void set_noise_white(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.noise.white = newValue; controlChanged(); }
    Q_PROPERTY(bool vco1_fm1_is_lfo_sine READ get_vco1_fm1_is_lfo_sine WRITE set_vco1_fm1_is_lfo_sine NOTIFY controlChanged)
    bool get_vco1_fm1_is_lfo_sine() { return m_synth.vco1.fm1_is_lfo_sine; }
    void set_vco1_fm1_is_lfo_sine(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco1.fm1_is_lfo_sine = newValue; controlChanged(); }
    Q_PROPERTY(bool vco1_fm2_is_sh_out READ get_vco1_fm2_is_sh_out WRITE set_vco1_fm2_is_sh_out NOTIFY controlChanged)
    bool get_vco1_fm2_is_sh_out() { return m_synth.vco1.fm2_is_sh_out; }
    void set_vco1_fm2_is_sh_out(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco1.fm2_is_sh_out = newValue; controlChanged(); }
    Q_PROPERTY(bool vco1_pwm_is_lfo READ get_vco1_pwm_is_lfo WRITE set_vco1_pwm_is_lfo NOTIFY controlChanged)
    bool get_vco1_pwm_is_lfo() { return m_synth.vco1.pwm_is_lfo; }
    void set_vco1_pwm_is_lfo(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco1.pwm_is_lfo = newValue; controlChanged(); }
    Q_PROPERTY(bool vco2_fm1_is_lfo_sine READ get_vco2_fm1_is_lfo_sine WRITE set_vco2_fm1_is_lfo_sine NOTIFY controlChanged)
    bool get_vco2_fm1_is_lfo_sine() { return m_synth.vco2.fm1_is_lfo_sine; }
    void set_vco2_fm1_is_lfo_sine(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco2.fm1_is_lfo_sine = newValue; controlChanged(); }
    Q_PROPERTY(bool vco2_fm2_is_sh_out READ get_vco2_fm2_is_sh_out WRITE set_vco2_fm2_is_sh_out NOTIFY controlChanged)
    bool get_vco2_fm2_is_sh_out() { return m_synth.vco2.fm2_is_sh_out; }
    void set_vco2_fm2_is_sh_out(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco2.fm2_is_sh_out = newValue; controlChanged(); }
    Q_PROPERTY(bool vco2_pwm_is_lfo READ get_vco2_pwm_is_lfo WRITE set_vco2_pwm_is_lfo NOTIFY controlChanged)
    bool get_vco2_pwm_is_lfo() { return m_synth.vco2.pwm_is_lfo; }
    void set_vco2_pwm_is_lfo(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vco2.pwm_is_lfo = newValue; controlChanged(); }
    Q_PROPERTY(bool sh_vco1_saw READ get_sh_vco1_saw WRITE set_sh_vco1_saw NOTIFY controlChanged)
    bool get_sh_vco1_saw() { return m_synth.sh.vco1_saw; }
    void set_sh_vco1_saw(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.sh.vco1_saw = newValue; controlChanged(); }
    Q_PROPERTY(bool sh_noise_gen READ get_sh_noise_gen WRITE set_sh_noise_gen NOTIFY controlChanged)
    bool get_sh_noise_gen() { return m_synth.sh.noise_gen; }
    void set_sh_noise_gen(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.sh.noise_gen = newValue; controlChanged(); }
    Q_PROPERTY(bool sh_lfo_trigger READ get_sh_lfo_trigger WRITE set_sh_lfo_trigger NOTIFY controlChanged)
    bool get_sh_lfo_trigger() { return m_synth.sh.lfo_trigger; }
    void set_sh_lfo_trigger(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.sh.lfo_trigger = newValue; controlChanged(); }
    Q_PROPERTY(bool mix_noise READ get_mix_noise WRITE set_mix_noise NOTIFY controlChanged)
    bool get_mix_noise() { return m_synth.mix.noise; }
    void set_mix_noise(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.mix.noise = newValue; controlChanged(); }
    Q_PROPERTY(bool mix_vco1_saw READ get_mix_vco1_saw WRITE set_mix_vco1_saw NOTIFY controlChanged)
    bool get_mix_vco1_saw() { return m_synth.mix.vco1_saw; }
    void set_mix_vco1_saw(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.mix.vco1_saw = newValue; controlChanged(); }
    Q_PROPERTY(bool mix_vco2_saw READ get_mix_vco2_saw WRITE set_mix_vco2_saw NOTIFY controlChanged)
    bool get_mix_vco2_saw() { return m_synth.mix.vco2_saw; }
    void set_mix_vco2_saw(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.mix.vco2_saw = newValue; controlChanged(); }
    Q_PROPERTY(bool vcf_mod1_kbd READ get_vcf_mod1_kbd WRITE set_vcf_mod1_kbd NOTIFY controlChanged)
    bool get_vcf_mod1_kbd() { return m_synth.vcf.mod1_kbd; }
    void set_vcf_mod1_kbd(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vcf.mod1_kbd = newValue; controlChanged(); }
    Q_PROPERTY(bool vcf_mod2_sh READ get_vcf_mod2_sh WRITE set_vcf_mod2_sh NOTIFY controlChanged)
    bool get_vcf_mod2_sh() { return m_synth.vcf.mod2_sh; }
    void set_vcf_mod2_sh(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vcf.mod2_sh = newValue; controlChanged(); }
    Q_PROPERTY(bool vcf_env_adsr READ get_vcf_env_adsr WRITE set_vcf_env_adsr NOTIFY controlChanged)
    bool get_vcf_env_adsr() { return m_synth.vcf.env_adsr; }
    void set_vcf_env_adsr(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vcf.env_adsr = newValue; controlChanged(); }
    Q_PROPERTY(bool vca_env_ar READ get_vca_env_ar WRITE set_vca_env_ar NOTIFY controlChanged)
    bool get_vca_env_ar() { return m_synth.vca.env_ar; }
    void set_vca_env_ar(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.vca.env_ar = newValue; controlChanged(); }
    Q_PROPERTY(bool adsr_kbd_trigger READ get_adsr_kbd_trigger WRITE set_adsr_kbd_trigger NOTIFY controlChanged)
    bool get_adsr_kbd_trigger() { return m_synth.adsr.kbd_trigger; }
    void set_adsr_kbd_trigger(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.adsr.kbd_trigger = newValue; controlChanged(); }
    Q_PROPERTY(bool adsr_kbd_repeat READ get_adsr_kbd_repeat WRITE set_adsr_kbd_repeat NOTIFY controlChanged)
    bool get_adsr_kbd_repeat() { return m_synth.adsr.kbd_repeat; }
    void set_adsr_kbd_repeat(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.adsr.kbd_repeat = newValue; controlChanged(); }
    Q_PROPERTY(bool ar_kbd_trigger READ get_ar_kbd_trigger WRITE set_ar_kbd_trigger NOTIFY controlChanged)
    bool get_ar_kbd_trigger() { return m_synth.ar.kbd_trigger; }
    void set_ar_kbd_trigger(bool newValue) { QMutexLocker locker(&m_device.mutex); m_synth.ar.kbd_trigger = newValue; controlChanged(); }

protected:
    QSettings settings;

public:
    QSynth(QObject *parent);

    Q_INVOKABLE void loadPreset(const QString &name);
    Q_INVOKABLE void savePreset(const QString &name);
};
