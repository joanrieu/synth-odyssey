#include "control.hpp"

void set_control_value(Synth& synth, const ControlValue& cv) {
    switch (cv.type) {
    case ControlType::FLOAT:
        switch (cv.float_change.control) {
        case FloatControl::VCO1_TUNE: synth.vco1.tune = cv.float_change.value; break;
        case FloatControl::VCO1_DETUNE: synth.vco1.detune = cv.float_change.value; break;
        case FloatControl::VCO2_TUNE: synth.vco2.tune = cv.float_change.value; break;
        case FloatControl::VCO2_DETUNE: synth.vco2.detune = cv.float_change.value; break;
        case FloatControl::LFO_FREQ: synth.lfo.freq = cv.float_change.value; break;
        case FloatControl::VCF_CUTOFF: synth.vcf.cutoff = cv.float_change.value; break;
        case FloatControl::VCF_RESO: synth.vcf.reso = cv.float_change.value; break;
        case FloatControl::HPF_CUTOFF: synth.hpf.cutoff = cv.float_change.value; break;
        case FloatControl::VCA_GAIN: synth.vca.gain = cv.float_change.value; break;
        case FloatControl::AR_ATTACK: synth.ar.attack = cv.float_change.value; break;
        case FloatControl::AR_RELEASE: synth.ar.release = cv.float_change.value; break;
        case FloatControl::VCO1_FM1: synth.vco1.fm1 = cv.float_change.value; break;
        case FloatControl::VCO1_FM2: synth.vco1.fm2 = cv.float_change.value; break;
        case FloatControl::VCO1_PW: synth.vco1.pw = cv.float_change.value; break;
        case FloatControl::VCO1_PWM: synth.vco1.pwm = cv.float_change.value; break;
        case FloatControl::VCO2_FM1: synth.vco2.fm1 = cv.float_change.value; break;
        case FloatControl::VCO2_FM2: synth.vco2.fm2 = cv.float_change.value; break;
        case FloatControl::VCO2_PW: synth.vco2.pw = cv.float_change.value; break;
        case FloatControl::VCO2_PWM: synth.vco2.pwm = cv.float_change.value; break;
        case FloatControl::SH_VCO1: synth.sh.vco1 = cv.float_change.value; break;
        case FloatControl::SH_NOISE: synth.sh.noise = cv.float_change.value; break;
        case FloatControl::SH_LAG: synth.sh.lag = cv.float_change.value; break;
        case FloatControl::MIX_NOISE_RING: synth.mix.noise_ring = cv.float_change.value; break;
        case FloatControl::MIX_VCO1: synth.mix.vco1 = cv.float_change.value; break;
        case FloatControl::MIX_VCO2: synth.mix.vco2 = cv.float_change.value; break;
        case FloatControl::VCF_MOD1: synth.vcf.mod1 = cv.float_change.value; break;
        case FloatControl::VCF_MOD2: synth.vcf.mod2 = cv.float_change.value; break;
        case FloatControl::VCF_ENV: synth.vcf.env = cv.float_change.value; break;
        case FloatControl::VCA_ENV: synth.vca.env = cv.float_change.value; break;
        case FloatControl::ADSR_ATTACK: synth.adsr.attack = cv.float_change.value; break;
        case FloatControl::ADSR_DECAY: synth.adsr.decay = cv.float_change.value; break;
        case FloatControl::ADSR_SUSTAIN: synth.adsr.sustain = cv.float_change.value; break;
        case FloatControl::ADSR_RELEASE: synth.adsr.release = cv.float_change.value; break;
        }
        break;

    case ControlType::BOOLEAN:
        switch (cv.boolean_change.control) {
        case BooleanControl::VCO1_KBD: synth.vco1.kbd = cv.boolean_change.value; break;
        case BooleanControl::VCO2_SYNC: synth.vco2.sync = cv.boolean_change.value; break;
        case BooleanControl::NOISE_WHITE: synth.noise.white = cv.boolean_change.value; break;
        case BooleanControl::VCO1_FM1_IS_LFO_SINE: synth.vco1.fm1_is_lfo_sine = cv.boolean_change.value; break;
        case BooleanControl::VCO1_FM2_IS_SH_OUT: synth.vco1.fm2_is_sh_out = cv.boolean_change.value; break;
        case BooleanControl::VCO1_PWM_IS_LFO: synth.vco1.pwm_is_lfo = cv.boolean_change.value; break;
        case BooleanControl::VCO2_FM1_IS_LFO_SINE: synth.vco2.fm1_is_lfo_sine = cv.boolean_change.value; break;
        case BooleanControl::VCO2_FM2_IS_SH_OUT: synth.vco2.fm2_is_sh_out = cv.boolean_change.value; break;
        case BooleanControl::VCO2_PWM_IS_LFO: synth.vco2.pwm_is_lfo = cv.boolean_change.value; break;
        case BooleanControl::SH_VCO1_SAW: synth.sh.vco1_saw = cv.boolean_change.value; break;
        case BooleanControl::SH_NOISE_GEN: synth.sh.noise_gen = cv.boolean_change.value; break;
        case BooleanControl::SH_LFO_TRIGGER: synth.sh.lfo_trigger = cv.boolean_change.value; break;
        case BooleanControl::MIX_NOISE: synth.mix.noise = cv.boolean_change.value; break;
        case BooleanControl::MIX_VCO1_SAW: synth.mix.vco1_saw = cv.boolean_change.value; break;
        case BooleanControl::MIX_VCO2_SAW: synth.mix.vco2_saw = cv.boolean_change.value; break;
        case BooleanControl::VCF_MOD1_KBD: synth.vcf.mod1_kbd = cv.boolean_change.value; break;
        case BooleanControl::VCF_MOD2_SH: synth.vcf.mod2_sh = cv.boolean_change.value; break;
        case BooleanControl::VCF_ENV_ADSR: synth.vcf.env_adsr = cv.boolean_change.value; break;
        case BooleanControl::VCA_ENV_AR: synth.vca.env_ar = cv.boolean_change.value; break;
        case BooleanControl::ADSR_KBD_TRIGGER: synth.adsr.kbd_trigger = cv.boolean_change.value; break;
        case BooleanControl::ADSR_KBD_REPEAT: synth.adsr.kbd_repeat = cv.boolean_change.value; break;
        case BooleanControl::AR_KBD_TRIGGER: synth.ar.kbd_trigger = cv.boolean_change.value; break;
        }
        break;
    }
}
