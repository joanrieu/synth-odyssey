#include "control.hpp"

ControlledSynth::ControlledSynth() {
    const auto sentinel = new ControlNode();
    sentinel->applied = true;
    control_head = control_reader = control_tail = sentinel;
}

ControlledSynth::~ControlledSynth() {
    while (control_head) {
        const auto old_head = control_head;
        control_head = old_head->next;
        delete old_head;
    }
}

void ControlledSynth::push_control(const Control& control) {
    // push new control
    control_tail->next = new ControlNode();
    control_tail->next->control = control;
    control_tail->has_next = true;
    control_tail = control_tail->next;
    // delete old controls
    while (control_head->releasable) {
        const auto old_head = control_head;
        control_head = old_head->next;
        delete old_head;
    }
}

float ControlledSynth::update() {
    while (true) {
        if (!control_reader->applied) {
            update_control(control_reader->control);
            control_reader->applied = true;
        }
        if (control_reader->has_next) {
            control_reader = control_reader->next;
            control_reader->releasable = true;
        } else {
            break;
        }
    }
    return Synth::update();
}

void ControlledSynth::update_control(const Control& control) {
    switch (control.type) {
    case ControlType::UNSIGNED:
        switch (control.cv.unsigned_cv.control) {
        case UnsignedControl::SAMPLE_RATE: sr = control.cv.unsigned_cv.value; break;
        }
        break;

    case ControlType::FLOAT:
        switch (control.cv.float_cv.control) {
        case FloatControl::VCO1_TUNE: vco1.tune = control.cv.float_cv.value; break;
        case FloatControl::VCO1_DETUNE: vco1.detune = control.cv.float_cv.value; break;
        case FloatControl::VCO2_TUNE: vco2.tune = control.cv.float_cv.value; break;
        case FloatControl::VCO2_DETUNE: vco2.detune = control.cv.float_cv.value; break;
        case FloatControl::LFO_FREQ: lfo.freq = control.cv.float_cv.value; break;
        case FloatControl::VCF_CUTOFF: vcf.cutoff = control.cv.float_cv.value; break;
        case FloatControl::VCF_RESO: vcf.reso = control.cv.float_cv.value; break;
        case FloatControl::HPF_CUTOFF: hpf.cutoff = control.cv.float_cv.value; break;
        case FloatControl::VCA_GAIN: vca.gain = control.cv.float_cv.value; break;
        case FloatControl::AR_ATTACK: ar.attack = control.cv.float_cv.value; break;
        case FloatControl::AR_RELEASE: ar.release = control.cv.float_cv.value; break;
        case FloatControl::VCO1_FM1: vco1.fm1 = control.cv.float_cv.value; break;
        case FloatControl::VCO1_FM2: vco1.fm2 = control.cv.float_cv.value; break;
        case FloatControl::VCO1_PW: vco1.pw = control.cv.float_cv.value; break;
        case FloatControl::VCO1_PWM: vco1.pwm = control.cv.float_cv.value; break;
        case FloatControl::VCO2_FM1: vco2.fm1 = control.cv.float_cv.value; break;
        case FloatControl::VCO2_FM2: vco2.fm2 = control.cv.float_cv.value; break;
        case FloatControl::VCO2_PW: vco2.pw = control.cv.float_cv.value; break;
        case FloatControl::VCO2_PWM: vco2.pwm = control.cv.float_cv.value; break;
        case FloatControl::SH_VCO1: sh.vco1 = control.cv.float_cv.value; break;
        case FloatControl::SH_NOISE: sh.noise = control.cv.float_cv.value; break;
        case FloatControl::SH_LAG: sh.lag = control.cv.float_cv.value; break;
        case FloatControl::MIX_NOISE_RING: mix.noise_ring = control.cv.float_cv.value; break;
        case FloatControl::MIX_VCO1: mix.vco1 = control.cv.float_cv.value; break;
        case FloatControl::MIX_VCO2: mix.vco2 = control.cv.float_cv.value; break;
        case FloatControl::VCF_MOD1: vcf.mod1 = control.cv.float_cv.value; break;
        case FloatControl::VCF_MOD2: vcf.mod2 = control.cv.float_cv.value; break;
        case FloatControl::VCF_ENV: vcf.env = control.cv.float_cv.value; break;
        case FloatControl::VCA_ENV: vca.env = control.cv.float_cv.value; break;
        case FloatControl::ADSR_ATTACK: adsr.attack = control.cv.float_cv.value; break;
        case FloatControl::ADSR_DECAY: adsr.decay = control.cv.float_cv.value; break;
        case FloatControl::ADSR_SUSTAIN: adsr.sustain = control.cv.float_cv.value; break;
        case FloatControl::ADSR_RELEASE: adsr.release = control.cv.float_cv.value; break;
        }
        break;

    case ControlType::BOOLEAN:
        switch (control.cv.boolean_cv.control) {
        case BooleanControl::VCO1_KBD: vco1.kbd = control.cv.boolean_cv.value; break;
        case BooleanControl::VCO2_SYNC: vco2.sync = control.cv.boolean_cv.value; break;
        case BooleanControl::NOISE_WHITE: noise.white = control.cv.boolean_cv.value; break;
        case BooleanControl::VCO1_FM1_IS_LFO_SINE: vco1.fm1_is_lfo_sine = control.cv.boolean_cv.value; break;
        case BooleanControl::VCO1_FM2_IS_SH_OUT: vco1.fm2_is_sh_out = control.cv.boolean_cv.value; break;
        case BooleanControl::VCO1_PWM_IS_LFO: vco1.pwm_is_lfo = control.cv.boolean_cv.value; break;
        case BooleanControl::VCO2_FM1_IS_LFO_SINE: vco2.fm1_is_lfo_sine = control.cv.boolean_cv.value; break;
        case BooleanControl::VCO2_FM2_IS_SH_OUT: vco2.fm2_is_sh_out = control.cv.boolean_cv.value; break;
        case BooleanControl::VCO2_PWM_IS_LFO: vco2.pwm_is_lfo = control.cv.boolean_cv.value; break;
        case BooleanControl::SH_VCO1_SAW: sh.vco1_saw = control.cv.boolean_cv.value; break;
        case BooleanControl::SH_NOISE_GEN: sh.noise_gen = control.cv.boolean_cv.value; break;
        case BooleanControl::SH_LFO_TRIGGER: sh.lfo_trigger = control.cv.boolean_cv.value; break;
        case BooleanControl::MIX_NOISE: mix.noise = control.cv.boolean_cv.value; break;
        case BooleanControl::MIX_VCO1_SAW: mix.vco1_saw = control.cv.boolean_cv.value; break;
        case BooleanControl::MIX_VCO2_SAW: mix.vco2_saw = control.cv.boolean_cv.value; break;
        case BooleanControl::VCF_MOD1_KBD: vcf.mod1_kbd = control.cv.boolean_cv.value; break;
        case BooleanControl::VCF_MOD2_SH: vcf.mod2_sh = control.cv.boolean_cv.value; break;
        case BooleanControl::VCF_ENV_ADSR: vcf.env_adsr = control.cv.boolean_cv.value; break;
        case BooleanControl::VCA_ENV_AR: vca.env_ar = control.cv.boolean_cv.value; break;
        case BooleanControl::ADSR_KBD_TRIGGER: adsr.kbd_trigger = control.cv.boolean_cv.value; break;
        case BooleanControl::ADSR_KBD_REPEAT: adsr.kbd_repeat = control.cv.boolean_cv.value; break;
        case BooleanControl::AR_KBD_TRIGGER: ar.kbd_trigger = control.cv.boolean_cv.value; break;
        }
        break;
    }
}
