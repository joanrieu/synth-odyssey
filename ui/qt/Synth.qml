pragma Singleton
import QtQuick 2.12

QtObject {
    property real vco1_tune: 0
    property real vco1_detune: 0
    property real vco2_tune: 0
    property real vco2_detune: 0
    property real lfo_freq: 0
    property real vcf_cutoff: 0
    property real vcf_reso: 0
    property real hpf_cutoff: 0
    property real vca_gain: 0
    property real ar_attack: 0
    property real ar_release: 0
    property real vco1_fm1: 0
    property real vco1_fm2: 0
    property real vco1_pw: 0
    property real vco1_pwm: 0
    property real vco2_fm1: 0
    property real vco2_fm2: 0
    property real vco2_pw: 0
    property real vco2_pwm: 0
    property real sh_vco1: 0
    property real sh_noise: 0
    property real sh_lag: 0
    property real mix_noise_ring: 0
    property real mix_vco1: 0
    property real mix_vco2: 0
    property real vcf_mod1: 0
    property real vcf_mod2: 0
    property real vcf_env: 0
    property real vca_env: 0
    property real adsr_attack: 0
    property real adsr_decay: 0
    property real adsr_sustain: 0
    property real adsr_release: 0

    property bool vco1_kbd: false
    property bool vco2_sync: false
    property bool noise_white: false
    property bool vco1_fm1_is_lfo_sine: false
    property bool vco1_fm2_is_sh_out: false
    property bool vco1_pwm_is_lfo: false
    property bool vco2_fm1_is_lfo_sine: false
    property bool vco2_fm2_is_sh_out: false
    property bool vco2_pwm_is_lfo: false
    property bool sh_vco1_saw: false
    property bool sh_noise_gen: false
    property bool sh_lfo_trigger: false
    property bool mix_noise: false
    property bool mix_vco1_saw: false
    property bool mix_vco2_saw: false
    property bool vcf_mod1_kbd: false
    property bool vcf_mod2_sh: false
    property bool vcf_env_adsr: false
    property bool vca_env_ar: false
    property bool adsr_kbd_trigger: false
    property bool adsr_kbd_repeat: false
    property bool ar_kbd_trigger: false
}
