#ifndef QSYNTH_H
#define QSYNTH_H

#include <QObject>
#include <iostream>

class QSynth : public QObject
{
    Q_OBJECT

    Q_PROPERTY(float vco1_tune MEMBER vco1_tune WRITE set_vco1_tune NOTIFY vco1_tune_changed)
    Q_PROPERTY(float vco1_detune MEMBER vco1_detune WRITE set_vco1_detune NOTIFY vco1_detune_changed)
    Q_PROPERTY(float vco2_tune MEMBER vco2_tune WRITE set_vco2_tune NOTIFY vco2_tune_changed)
    Q_PROPERTY(float vco2_detune MEMBER vco2_detune WRITE set_vco2_detune NOTIFY vco2_detune_changed)
    Q_PROPERTY(float lfo_freq MEMBER lfo_freq WRITE set_lfo_freq NOTIFY lfo_freq_changed)
    Q_PROPERTY(float vcf_cutoff MEMBER vcf_cutoff WRITE set_vcf_cutoff NOTIFY vcf_cutoff_changed)
    Q_PROPERTY(float vcf_reso MEMBER vcf_reso WRITE set_vcf_reso NOTIFY vcf_reso_changed)
    Q_PROPERTY(float hpf_cutoff MEMBER hpf_cutoff WRITE set_hpf_cutoff NOTIFY hpf_cutoff_changed)
    Q_PROPERTY(float vca_gain MEMBER vca_gain WRITE set_vca_gain NOTIFY vca_gain_changed)
    Q_PROPERTY(float ar_attack MEMBER ar_attack WRITE set_ar_attack NOTIFY ar_attack_changed)
    Q_PROPERTY(float ar_release MEMBER ar_release WRITE set_ar_release NOTIFY ar_release_changed)
    Q_PROPERTY(float vco1_fm1 MEMBER vco1_fm1 WRITE set_vco1_fm1 NOTIFY vco1_fm1_changed)
    Q_PROPERTY(float vco1_fm2 MEMBER vco1_fm2 WRITE set_vco1_fm2 NOTIFY vco1_fm2_changed)
    Q_PROPERTY(float vco1_pw MEMBER vco1_pw WRITE set_vco1_pw NOTIFY vco1_pw_changed)
    Q_PROPERTY(float vco1_pwm MEMBER vco1_pwm WRITE set_vco1_pwm NOTIFY vco1_pwm_changed)
    Q_PROPERTY(float vco2_fm1 MEMBER vco2_fm1 WRITE set_vco2_fm1 NOTIFY vco2_fm1_changed)
    Q_PROPERTY(float vco2_fm2 MEMBER vco2_fm2 WRITE set_vco2_fm2 NOTIFY vco2_fm2_changed)
    Q_PROPERTY(float vco2_pw MEMBER vco2_pw WRITE set_vco2_pw NOTIFY vco2_pw_changed)
    Q_PROPERTY(float vco2_pwm MEMBER vco2_pwm WRITE set_vco2_pwm NOTIFY vco2_pwm_changed)
    Q_PROPERTY(float sh_vco1 MEMBER sh_vco1 WRITE set_sh_vco1 NOTIFY sh_vco1_changed)
    Q_PROPERTY(float sh_noise MEMBER sh_noise WRITE set_sh_noise NOTIFY sh_noise_changed)
    Q_PROPERTY(float sh_lag MEMBER sh_lag WRITE set_sh_lag NOTIFY sh_lag_changed)
    Q_PROPERTY(float mix_noise_ring MEMBER mix_noise_ring WRITE set_mix_noise_ring NOTIFY mix_noise_ring_changed)
    Q_PROPERTY(float mix_vco1 MEMBER mix_vco1 WRITE set_mix_vco1 NOTIFY mix_vco1_changed)
    Q_PROPERTY(float mix_vco2 MEMBER mix_vco2 WRITE set_mix_vco2 NOTIFY mix_vco2_changed)
    Q_PROPERTY(float vcf_mod1 MEMBER vcf_mod1 WRITE set_vcf_mod1 NOTIFY vcf_mod1_changed)
    Q_PROPERTY(float vcf_mod2 MEMBER vcf_mod2 WRITE set_vcf_mod2 NOTIFY vcf_mod2_changed)
    Q_PROPERTY(float vcf_env MEMBER vcf_env WRITE set_vcf_env NOTIFY vcf_env_changed)
    Q_PROPERTY(float vca_env MEMBER vca_env WRITE set_vca_env NOTIFY vca_env_changed)
    Q_PROPERTY(float adsr_attack MEMBER adsr_attack WRITE set_adsr_attack NOTIFY adsr_attack_changed)
    Q_PROPERTY(float adsr_decay MEMBER adsr_decay WRITE set_adsr_decay NOTIFY adsr_decay_changed)
    Q_PROPERTY(float adsr_sustain MEMBER adsr_sustain WRITE set_adsr_sustain NOTIFY adsr_sustain_changed)
    Q_PROPERTY(float adsr_release MEMBER adsr_release WRITE set_adsr_release NOTIFY adsr_release_changed)
    Q_PROPERTY(bool vco1_kbd MEMBER vco1_kbd WRITE set_vco1_kbd NOTIFY vco1_kbd_changed)
    Q_PROPERTY(bool vco2_sync MEMBER vco2_sync WRITE set_vco2_sync NOTIFY vco2_sync_changed)
    Q_PROPERTY(bool noise_white MEMBER noise_white WRITE set_noise_white NOTIFY noise_white_changed)
    Q_PROPERTY(bool vco1_fm1_is_lfo_sine MEMBER vco1_fm1_is_lfo_sine WRITE set_vco1_fm1_is_lfo_sine NOTIFY vco1_fm1_is_lfo_sine_changed)
    Q_PROPERTY(bool vco1_fm2_is_sh_out MEMBER vco1_fm2_is_sh_out WRITE set_vco1_fm2_is_sh_out NOTIFY vco1_fm2_is_sh_out_changed)
    Q_PROPERTY(bool vco1_pwm_is_lfo MEMBER vco1_pwm_is_lfo WRITE set_vco1_pwm_is_lfo NOTIFY vco1_pwm_is_lfo_changed)
    Q_PROPERTY(bool vco2_fm1_is_lfo_sine MEMBER vco2_fm1_is_lfo_sine WRITE set_vco2_fm1_is_lfo_sine NOTIFY vco2_fm1_is_lfo_sine_changed)
    Q_PROPERTY(bool vco2_fm2_is_sh_out MEMBER vco2_fm2_is_sh_out WRITE set_vco2_fm2_is_sh_out NOTIFY vco2_fm2_is_sh_out_changed)
    Q_PROPERTY(bool vco2_pwm_is_lfo MEMBER vco2_pwm_is_lfo WRITE set_vco2_pwm_is_lfo NOTIFY vco2_pwm_is_lfo_changed)
    Q_PROPERTY(bool sh_vco1_saw MEMBER sh_vco1_saw WRITE set_sh_vco1_saw NOTIFY sh_vco1_saw_changed)
    Q_PROPERTY(bool sh_noise_gen MEMBER sh_noise_gen WRITE set_sh_noise_gen NOTIFY sh_noise_gen_changed)
    Q_PROPERTY(bool sh_lfo_trigger MEMBER sh_lfo_trigger WRITE set_sh_lfo_trigger NOTIFY sh_lfo_trigger_changed)
    Q_PROPERTY(bool mix_noise MEMBER mix_noise WRITE set_mix_noise NOTIFY mix_noise_changed)
    Q_PROPERTY(bool mix_vco1_saw MEMBER mix_vco1_saw WRITE set_mix_vco1_saw NOTIFY mix_vco1_saw_changed)
    Q_PROPERTY(bool mix_vco2_saw MEMBER mix_vco2_saw WRITE set_mix_vco2_saw NOTIFY mix_vco2_saw_changed)
    Q_PROPERTY(bool vcf_mod1_kbd MEMBER vcf_mod1_kbd WRITE set_vcf_mod1_kbd NOTIFY vcf_mod1_kbd_changed)
    Q_PROPERTY(bool vcf_mod2_sh MEMBER vcf_mod2_sh WRITE set_vcf_mod2_sh NOTIFY vcf_mod2_sh_changed)
    Q_PROPERTY(bool vcf_env_adsr MEMBER vcf_env_adsr WRITE set_vcf_env_adsr NOTIFY vcf_env_adsr_changed)
    Q_PROPERTY(bool vca_env_ar MEMBER vca_env_ar WRITE set_vca_env_ar NOTIFY vca_env_ar_changed)
    Q_PROPERTY(bool adsr_kbd_trigger MEMBER adsr_kbd_trigger WRITE set_adsr_kbd_trigger NOTIFY adsr_kbd_trigger_changed)
    Q_PROPERTY(bool adsr_kbd_repeat MEMBER adsr_kbd_repeat WRITE set_adsr_kbd_repeat NOTIFY adsr_kbd_repeat_changed)
    Q_PROPERTY(bool ar_kbd_trigger MEMBER ar_kbd_trigger WRITE set_ar_kbd_trigger NOTIFY ar_kbd_trigger_changed)

signals:
    void vco1_tune_changed();
    void vco1_detune_changed();
    void vco2_tune_changed();
    void vco2_detune_changed();
    void lfo_freq_changed();
    void vcf_cutoff_changed();
    void vcf_reso_changed();
    void hpf_cutoff_changed();
    void vca_gain_changed();
    void ar_attack_changed();
    void ar_release_changed();
    void vco1_fm1_changed();
    void vco1_fm2_changed();
    void vco1_pw_changed();
    void vco1_pwm_changed();
    void vco2_fm1_changed();
    void vco2_fm2_changed();
    void vco2_pw_changed();
    void vco2_pwm_changed();
    void sh_vco1_changed();
    void sh_noise_changed();
    void sh_lag_changed();
    void mix_noise_ring_changed();
    void mix_vco1_changed();
    void mix_vco2_changed();
    void vcf_mod1_changed();
    void vcf_mod2_changed();
    void vcf_env_changed();
    void vca_env_changed();
    void adsr_attack_changed();
    void adsr_decay_changed();
    void adsr_sustain_changed();
    void adsr_release_changed();
    void vco1_kbd_changed();
    void vco2_sync_changed();
    void noise_white_changed();
    void vco1_fm1_is_lfo_sine_changed();
    void vco1_fm2_is_sh_out_changed();
    void vco1_pwm_is_lfo_changed();
    void vco2_fm1_is_lfo_sine_changed();
    void vco2_fm2_is_sh_out_changed();
    void vco2_pwm_is_lfo_changed();
    void sh_vco1_saw_changed();
    void sh_noise_gen_changed();
    void sh_lfo_trigger_changed();
    void mix_noise_changed();
    void mix_vco1_saw_changed();
    void mix_vco2_saw_changed();
    void vcf_mod1_kbd_changed();
    void vcf_mod2_sh_changed();
    void vcf_env_adsr_changed();
    void vca_env_ar_changed();
    void adsr_kbd_trigger_changed();
    void adsr_kbd_repeat_changed();
    void ar_kbd_trigger_changed();

private:
    void set_vco1_tune(float new_vco1_tune) { vco1_tune = new_vco1_tune; std::cout << "set vco1_tune=" << vco1_tune << std::endl; vco1_tune_changed(); }
    void set_vco1_detune(float new_vco1_detune) { vco1_detune = new_vco1_detune; std::cout << "set vco1_detune=" << vco1_detune << std::endl; vco1_detune_changed(); }
    void set_vco2_tune(float new_vco2_tune) { vco2_tune = new_vco2_tune; std::cout << "set vco2_tune=" << vco2_tune << std::endl; vco2_tune_changed(); }
    void set_vco2_detune(float new_vco2_detune) { vco2_detune = new_vco2_detune; std::cout << "set vco2_detune=" << vco2_detune << std::endl; vco2_detune_changed(); }
    void set_lfo_freq(float new_lfo_freq) { lfo_freq = new_lfo_freq; std::cout << "set lfo_freq=" << lfo_freq << std::endl; lfo_freq_changed(); }
    void set_vcf_cutoff(float new_vcf_cutoff) { vcf_cutoff = new_vcf_cutoff; std::cout << "set vcf_cutoff=" << vcf_cutoff << std::endl; vcf_cutoff_changed(); }
    void set_vcf_reso(float new_vcf_reso) { vcf_reso = new_vcf_reso; std::cout << "set vcf_reso=" << vcf_reso << std::endl; vcf_reso_changed(); }
    void set_hpf_cutoff(float new_hpf_cutoff) { hpf_cutoff = new_hpf_cutoff; std::cout << "set hpf_cutoff=" << hpf_cutoff << std::endl; hpf_cutoff_changed(); }
    void set_vca_gain(float new_vca_gain) { vca_gain = new_vca_gain; std::cout << "set vca_gain=" << vca_gain << std::endl; vca_gain_changed(); }
    void set_ar_attack(float new_ar_attack) { ar_attack = new_ar_attack; std::cout << "set ar_attack=" << ar_attack << std::endl; ar_attack_changed(); }
    void set_ar_release(float new_ar_release) { ar_release = new_ar_release; std::cout << "set ar_release=" << ar_release << std::endl; ar_release_changed(); }
    void set_vco1_fm1(float new_vco1_fm1) { vco1_fm1 = new_vco1_fm1; std::cout << "set vco1_fm1=" << vco1_fm1 << std::endl; vco1_fm1_changed(); }
    void set_vco1_fm2(float new_vco1_fm2) { vco1_fm2 = new_vco1_fm2; std::cout << "set vco1_fm2=" << vco1_fm2 << std::endl; vco1_fm2_changed(); }
    void set_vco1_pw(float new_vco1_pw) { vco1_pw = new_vco1_pw; std::cout << "set vco1_pw=" << vco1_pw << std::endl; vco1_pw_changed(); }
    void set_vco1_pwm(float new_vco1_pwm) { vco1_pwm = new_vco1_pwm; std::cout << "set vco1_pwm=" << vco1_pwm << std::endl; vco1_pwm_changed(); }
    void set_vco2_fm1(float new_vco2_fm1) { vco2_fm1 = new_vco2_fm1; std::cout << "set vco2_fm1=" << vco2_fm1 << std::endl; vco2_fm1_changed(); }
    void set_vco2_fm2(float new_vco2_fm2) { vco2_fm2 = new_vco2_fm2; std::cout << "set vco2_fm2=" << vco2_fm2 << std::endl; vco2_fm2_changed(); }
    void set_vco2_pw(float new_vco2_pw) { vco2_pw = new_vco2_pw; std::cout << "set vco2_pw=" << vco2_pw << std::endl; vco2_pw_changed(); }
    void set_vco2_pwm(float new_vco2_pwm) { vco2_pwm = new_vco2_pwm; std::cout << "set vco2_pwm=" << vco2_pwm << std::endl; vco2_pwm_changed(); }
    void set_sh_vco1(float new_sh_vco1) { sh_vco1 = new_sh_vco1; std::cout << "set sh_vco1=" << sh_vco1 << std::endl; sh_vco1_changed(); }
    void set_sh_noise(float new_sh_noise) { sh_noise = new_sh_noise; std::cout << "set sh_noise=" << sh_noise << std::endl; sh_noise_changed(); }
    void set_sh_lag(float new_sh_lag) { sh_lag = new_sh_lag; std::cout << "set sh_lag=" << sh_lag << std::endl; sh_lag_changed(); }
    void set_mix_noise_ring(float new_mix_noise_ring) { mix_noise_ring = new_mix_noise_ring; std::cout << "set mix_noise_ring=" << mix_noise_ring << std::endl; mix_noise_ring_changed(); }
    void set_mix_vco1(float new_mix_vco1) { mix_vco1 = new_mix_vco1; std::cout << "set mix_vco1=" << mix_vco1 << std::endl; mix_vco1_changed(); }
    void set_mix_vco2(float new_mix_vco2) { mix_vco2 = new_mix_vco2; std::cout << "set mix_vco2=" << mix_vco2 << std::endl; mix_vco2_changed(); }
    void set_vcf_mod1(float new_vcf_mod1) { vcf_mod1 = new_vcf_mod1; std::cout << "set vcf_mod1=" << vcf_mod1 << std::endl; vcf_mod1_changed(); }
    void set_vcf_mod2(float new_vcf_mod2) { vcf_mod2 = new_vcf_mod2; std::cout << "set vcf_mod2=" << vcf_mod2 << std::endl; vcf_mod2_changed(); }
    void set_vcf_env(float new_vcf_env) { vcf_env = new_vcf_env; std::cout << "set vcf_env=" << vcf_env << std::endl; vcf_env_changed(); }
    void set_vca_env(float new_vca_env) { vca_env = new_vca_env; std::cout << "set vca_env=" << vca_env << std::endl; vca_env_changed(); }
    void set_adsr_attack(float new_adsr_attack) { adsr_attack = new_adsr_attack; std::cout << "set adsr_attack=" << adsr_attack << std::endl; adsr_attack_changed(); }
    void set_adsr_decay(float new_adsr_decay) { adsr_decay = new_adsr_decay; std::cout << "set adsr_decay=" << adsr_decay << std::endl; adsr_decay_changed(); }
    void set_adsr_sustain(float new_adsr_sustain) { adsr_sustain = new_adsr_sustain; std::cout << "set adsr_sustain=" << adsr_sustain << std::endl; adsr_sustain_changed(); }
    void set_adsr_release(float new_adsr_release) { adsr_release = new_adsr_release; std::cout << "set adsr_release=" << adsr_release << std::endl; adsr_release_changed(); }
    void set_vco1_kbd(bool new_vco1_kbd) { vco1_kbd = new_vco1_kbd; std::cout << "set vco1_kbd=" << vco1_kbd << std::endl; vco1_kbd_changed(); }
    void set_vco2_sync(bool new_vco2_sync) { vco2_sync = new_vco2_sync; std::cout << "set vco2_sync=" << vco2_sync << std::endl; vco2_sync_changed(); }
    void set_noise_white(bool new_noise_white) { noise_white = new_noise_white; std::cout << "set noise_white=" << noise_white << std::endl; noise_white_changed(); }
    void set_vco1_fm1_is_lfo_sine(bool new_vco1_fm1_is_lfo_sine) { vco1_fm1_is_lfo_sine = new_vco1_fm1_is_lfo_sine; std::cout << "set vco1_fm1_is_lfo_sine=" << vco1_fm1_is_lfo_sine << std::endl; vco1_fm1_is_lfo_sine_changed(); }
    void set_vco1_fm2_is_sh_out(bool new_vco1_fm2_is_sh_out) { vco1_fm2_is_sh_out = new_vco1_fm2_is_sh_out; std::cout << "set vco1_fm2_is_sh_out=" << vco1_fm2_is_sh_out << std::endl; vco1_fm2_is_sh_out_changed(); }
    void set_vco1_pwm_is_lfo(bool new_vco1_pwm_is_lfo) { vco1_pwm_is_lfo = new_vco1_pwm_is_lfo; std::cout << "set vco1_pwm_is_lfo=" << vco1_pwm_is_lfo << std::endl; vco1_pwm_is_lfo_changed(); }
    void set_vco2_fm1_is_lfo_sine(bool new_vco2_fm1_is_lfo_sine) { vco2_fm1_is_lfo_sine = new_vco2_fm1_is_lfo_sine; std::cout << "set vco2_fm1_is_lfo_sine=" << vco2_fm1_is_lfo_sine << std::endl; vco2_fm1_is_lfo_sine_changed(); }
    void set_vco2_fm2_is_sh_out(bool new_vco2_fm2_is_sh_out) { vco2_fm2_is_sh_out = new_vco2_fm2_is_sh_out; std::cout << "set vco2_fm2_is_sh_out=" << vco2_fm2_is_sh_out << std::endl; vco2_fm2_is_sh_out_changed(); }
    void set_vco2_pwm_is_lfo(bool new_vco2_pwm_is_lfo) { vco2_pwm_is_lfo = new_vco2_pwm_is_lfo; std::cout << "set vco2_pwm_is_lfo=" << vco2_pwm_is_lfo << std::endl; vco2_pwm_is_lfo_changed(); }
    void set_sh_vco1_saw(bool new_sh_vco1_saw) { sh_vco1_saw = new_sh_vco1_saw; std::cout << "set sh_vco1_saw=" << sh_vco1_saw << std::endl; sh_vco1_saw_changed(); }
    void set_sh_noise_gen(bool new_sh_noise_gen) { sh_noise_gen = new_sh_noise_gen; std::cout << "set sh_noise_gen=" << sh_noise_gen << std::endl; sh_noise_gen_changed(); }
    void set_sh_lfo_trigger(bool new_sh_lfo_trigger) { sh_lfo_trigger = new_sh_lfo_trigger; std::cout << "set sh_lfo_trigger=" << sh_lfo_trigger << std::endl; sh_lfo_trigger_changed(); }
    void set_mix_noise(bool new_mix_noise) { mix_noise = new_mix_noise; std::cout << "set mix_noise=" << mix_noise << std::endl; mix_noise_changed(); }
    void set_mix_vco1_saw(bool new_mix_vco1_saw) { mix_vco1_saw = new_mix_vco1_saw; std::cout << "set mix_vco1_saw=" << mix_vco1_saw << std::endl; mix_vco1_saw_changed(); }
    void set_mix_vco2_saw(bool new_mix_vco2_saw) { mix_vco2_saw = new_mix_vco2_saw; std::cout << "set mix_vco2_saw=" << mix_vco2_saw << std::endl; mix_vco2_saw_changed(); }
    void set_vcf_mod1_kbd(bool new_vcf_mod1_kbd) { vcf_mod1_kbd = new_vcf_mod1_kbd; std::cout << "set vcf_mod1_kbd=" << vcf_mod1_kbd << std::endl; vcf_mod1_kbd_changed(); }
    void set_vcf_mod2_sh(bool new_vcf_mod2_sh) { vcf_mod2_sh = new_vcf_mod2_sh; std::cout << "set vcf_mod2_sh=" << vcf_mod2_sh << std::endl; vcf_mod2_sh_changed(); }
    void set_vcf_env_adsr(bool new_vcf_env_adsr) { vcf_env_adsr = new_vcf_env_adsr; std::cout << "set vcf_env_adsr=" << vcf_env_adsr << std::endl; vcf_env_adsr_changed(); }
    void set_vca_env_ar(bool new_vca_env_ar) { vca_env_ar = new_vca_env_ar; std::cout << "set vca_env_ar=" << vca_env_ar << std::endl; vca_env_ar_changed(); }
    void set_adsr_kbd_trigger(bool new_adsr_kbd_trigger) { adsr_kbd_trigger = new_adsr_kbd_trigger; std::cout << "set adsr_kbd_trigger=" << adsr_kbd_trigger << std::endl; adsr_kbd_trigger_changed(); }
    void set_adsr_kbd_repeat(bool new_adsr_kbd_repeat) { adsr_kbd_repeat = new_adsr_kbd_repeat; std::cout << "set adsr_kbd_repeat=" << adsr_kbd_repeat << std::endl; adsr_kbd_repeat_changed(); }
    void set_ar_kbd_trigger(bool new_ar_kbd_trigger) { ar_kbd_trigger = new_ar_kbd_trigger; std::cout << "set ar_kbd_trigger=" << ar_kbd_trigger << std::endl; ar_kbd_trigger_changed(); }

private:
    float vco1_tune;
    float vco1_detune;
    float vco2_tune;
    float vco2_detune;
    float lfo_freq;
    float vcf_cutoff;
    float vcf_reso;
    float hpf_cutoff;
    float vca_gain;
    float ar_attack;
    float ar_release;
    float vco1_fm1;
    float vco1_fm2;
    float vco1_pw;
    float vco1_pwm;
    float vco2_fm1;
    float vco2_fm2;
    float vco2_pw;
    float vco2_pwm;
    float sh_vco1;
    float sh_noise;
    float sh_lag;
    float mix_noise_ring;
    float mix_vco1;
    float mix_vco2;
    float vcf_mod1;
    float vcf_mod2;
    float vcf_env;
    float vca_env;
    float adsr_attack;
    float adsr_decay;
    float adsr_sustain;
    float adsr_release;
    bool vco1_kbd;
    bool vco2_sync;
    bool noise_white;
    bool vco1_fm1_is_lfo_sine;
    bool vco1_fm2_is_sh_out;
    bool vco1_pwm_is_lfo;
    bool vco2_fm1_is_lfo_sine;
    bool vco2_fm2_is_sh_out;
    bool vco2_pwm_is_lfo;
    bool sh_vco1_saw;
    bool sh_noise_gen;
    bool sh_lfo_trigger;
    bool mix_noise;
    bool mix_vco1_saw;
    bool mix_vco2_saw;
    bool vcf_mod1_kbd;
    bool vcf_mod2_sh;
    bool vcf_env_adsr;
    bool vca_env_ar;
    bool adsr_kbd_trigger;
    bool adsr_kbd_repeat;
    bool ar_kbd_trigger;
};

#endif // QSYNTH_H
