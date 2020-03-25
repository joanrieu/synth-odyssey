#include "control.hpp"

SynthController::SynthController() {
    const auto sentinel = new ControlNode();
    sentinel->applied = true;
    control_head = control_reader = control_tail = sentinel;
}

SynthController::~SynthController() {
    while (control_head) {
        const auto old_head = control_head;
        control_head = old_head->next;
        delete old_head;
    }
}

void SynthController::push_control(const Control& control) {
    // push new control
    control_tail->next = new ControlNode();
    control_tail->next->type = control.type;
    control_tail->next->cv = control.cv;
    control_tail->has_next = true;
    control_tail = control_tail->next;
    // delete old controls
    while (control_head->releasable) {
        const auto old_head = control_head;
        control_head = old_head->next;
        delete old_head;
    }
}

void SynthController::update() {
    while (true) {
        if (!control_reader->applied) {
            update_control(*control_reader);
            control_reader->applied = true;
        }
        if (control_reader->has_next) {
            control_reader = control_reader->next;
            control_reader->releasable = true;
        } else {
            break;
        }
    }
    m_synth.update();
}

void SynthController::update_control(const Control& control) {
    switch (control.type) {
    case ControlType::FLOAT:
        switch (control.cv.float_cv.control) {
        case FloatControl::VCO1_TUNE: m_synth.vco1.tune = control.cv.float_cv.value; break;
        case FloatControl::VCO1_DETUNE: m_synth.vco1.detune = control.cv.float_cv.value; break;
        case FloatControl::VCO2_TUNE: m_synth.vco2.tune = control.cv.float_cv.value; break;
        case FloatControl::VCO2_DETUNE: m_synth.vco2.detune = control.cv.float_cv.value; break;
        case FloatControl::LFO_FREQ: m_synth.lfo.freq = control.cv.float_cv.value; break;
        case FloatControl::VCF_CUTOFF: m_synth.vcf.cutoff = control.cv.float_cv.value; break;
        case FloatControl::VCF_RESO: m_synth.vcf.reso = control.cv.float_cv.value; break;
        case FloatControl::HPF_CUTOFF: m_synth.hpf.cutoff = control.cv.float_cv.value; break;
        case FloatControl::VCA_GAIN: m_synth.vca.gain = control.cv.float_cv.value; break;
        case FloatControl::AR_ATTACK: m_synth.ar.attack = control.cv.float_cv.value; break;
        case FloatControl::AR_RELEASE: m_synth.ar.release = control.cv.float_cv.value; break;
        case FloatControl::VCO1_FM1: m_synth.vco1.fm1 = control.cv.float_cv.value; break;
        case FloatControl::VCO1_FM2: m_synth.vco1.fm2 = control.cv.float_cv.value; break;
        case FloatControl::VCO1_PW: m_synth.vco1.pw = control.cv.float_cv.value; break;
        case FloatControl::VCO1_PWM: m_synth.vco1.pwm = control.cv.float_cv.value; break;
        case FloatControl::VCO2_FM1: m_synth.vco2.fm1 = control.cv.float_cv.value; break;
        case FloatControl::VCO2_FM2: m_synth.vco2.fm2 = control.cv.float_cv.value; break;
        case FloatControl::VCO2_PW: m_synth.vco2.pw = control.cv.float_cv.value; break;
        case FloatControl::VCO2_PWM: m_synth.vco2.pwm = control.cv.float_cv.value; break;
        case FloatControl::SH_VCO1: m_synth.sh.vco1 = control.cv.float_cv.value; break;
        case FloatControl::SH_NOISE: m_synth.sh.noise = control.cv.float_cv.value; break;
        case FloatControl::SH_LAG: m_synth.sh.lag = control.cv.float_cv.value; break;
        case FloatControl::MIX_NOISE_RING: m_synth.mix.noise_ring = control.cv.float_cv.value; break;
        case FloatControl::MIX_VCO1: m_synth.mix.vco1 = control.cv.float_cv.value; break;
        case FloatControl::MIX_VCO2: m_synth.mix.vco2 = control.cv.float_cv.value; break;
        case FloatControl::VCF_MOD1: m_synth.vcf.mod1 = control.cv.float_cv.value; break;
        case FloatControl::VCF_MOD2: m_synth.vcf.mod2 = control.cv.float_cv.value; break;
        case FloatControl::VCF_ENV: m_synth.vcf.env = control.cv.float_cv.value; break;
        case FloatControl::VCA_ENV: m_synth.vca.env = control.cv.float_cv.value; break;
        case FloatControl::ADSR_ATTACK: m_synth.adsr.attack = control.cv.float_cv.value; break;
        case FloatControl::ADSR_DECAY: m_synth.adsr.decay = control.cv.float_cv.value; break;
        case FloatControl::ADSR_SUSTAIN: m_synth.adsr.sustain = control.cv.float_cv.value; break;
        case FloatControl::ADSR_RELEASE: m_synth.adsr.release = control.cv.float_cv.value; break;
        }
        break;

    case ControlType::BOOLEAN:
        switch (control.cv.boolean_cv.control) {
        case BooleanControl::VCO1_KBD: m_synth.vco1.kbd = control.cv.boolean_cv.value; break;
        case BooleanControl::VCO2_SYNC: m_synth.vco2.sync = control.cv.boolean_cv.value; break;
        case BooleanControl::NOISE_WHITE: m_synth.noise.white = control.cv.boolean_cv.value; break;
        case BooleanControl::VCO1_FM1_IS_LFO_SINE: m_synth.vco1.fm1_is_lfo_sine = control.cv.boolean_cv.value; break;
        case BooleanControl::VCO1_FM2_IS_SH_OUT: m_synth.vco1.fm2_is_sh_out = control.cv.boolean_cv.value; break;
        case BooleanControl::VCO1_PWM_IS_LFO: m_synth.vco1.pwm_is_lfo = control.cv.boolean_cv.value; break;
        case BooleanControl::VCO2_FM1_IS_LFO_SINE: m_synth.vco2.fm1_is_lfo_sine = control.cv.boolean_cv.value; break;
        case BooleanControl::VCO2_FM2_IS_SH_OUT: m_synth.vco2.fm2_is_sh_out = control.cv.boolean_cv.value; break;
        case BooleanControl::VCO2_PWM_IS_LFO: m_synth.vco2.pwm_is_lfo = control.cv.boolean_cv.value; break;
        case BooleanControl::SH_VCO1_SAW: m_synth.sh.vco1_saw = control.cv.boolean_cv.value; break;
        case BooleanControl::SH_NOISE_GEN: m_synth.sh.noise_gen = control.cv.boolean_cv.value; break;
        case BooleanControl::SH_LFO_TRIGGER: m_synth.sh.lfo_trigger = control.cv.boolean_cv.value; break;
        case BooleanControl::MIX_NOISE: m_synth.mix.noise = control.cv.boolean_cv.value; break;
        case BooleanControl::MIX_VCO1_SAW: m_synth.mix.vco1_saw = control.cv.boolean_cv.value; break;
        case BooleanControl::MIX_VCO2_SAW: m_synth.mix.vco2_saw = control.cv.boolean_cv.value; break;
        case BooleanControl::VCF_MOD1_KBD: m_synth.vcf.mod1_kbd = control.cv.boolean_cv.value; break;
        case BooleanControl::VCF_MOD2_SH: m_synth.vcf.mod2_sh = control.cv.boolean_cv.value; break;
        case BooleanControl::VCF_ENV_ADSR: m_synth.vcf.env_adsr = control.cv.boolean_cv.value; break;
        case BooleanControl::VCA_ENV_AR: m_synth.vca.env_ar = control.cv.boolean_cv.value; break;
        case BooleanControl::ADSR_KBD_TRIGGER: m_synth.adsr.kbd_trigger = control.cv.boolean_cv.value; break;
        case BooleanControl::ADSR_KBD_REPEAT: m_synth.adsr.kbd_repeat = control.cv.boolean_cv.value; break;
        case BooleanControl::AR_KBD_TRIGGER: m_synth.ar.kbd_trigger = control.cv.boolean_cv.value; break;
        }
        break;
    }
}
