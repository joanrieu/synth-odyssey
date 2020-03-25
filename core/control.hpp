#pragma once

#include <atomic>

#include "synth.hpp"

enum class FloatControl {
    VCO1_TUNE,
    VCO1_DETUNE,
    VCO2_TUNE,
    VCO2_DETUNE,
    LFO_FREQ,
    VCF_CUTOFF,
    VCF_RESO,
    HPF_CUTOFF,
    VCA_GAIN,
    AR_ATTACK,
    AR_RELEASE,
    VCO1_FM1,
    VCO1_FM2,
    VCO1_PW,
    VCO1_PWM,
    VCO2_FM1,
    VCO2_FM2,
    VCO2_PW,
    VCO2_PWM,
    SH_VCO1,
    SH_NOISE,
    SH_LAG,
    MIX_NOISE_RING,
    MIX_VCO1,
    MIX_VCO2,
    VCF_MOD1,
    VCF_MOD2,
    VCF_ENV,
    VCA_ENV,
    ADSR_ATTACK,
    ADSR_DECAY,
    ADSR_SUSTAIN,
    ADSR_RELEASE,
};

enum class BooleanControl {
    VCO1_KBD,
    VCO2_SYNC,
    NOISE_WHITE,
    VCO1_FM1_IS_LFO_SINE,
    VCO1_FM2_IS_SH_OUT,
    VCO1_PWM_IS_LFO,
    VCO2_FM1_IS_LFO_SINE,
    VCO2_FM2_IS_SH_OUT,
    VCO2_PWM_IS_LFO,
    SH_VCO1_SAW,
    SH_NOISE_GEN,
    SH_LFO_TRIGGER,
    MIX_NOISE,
    MIX_VCO1_SAW,
    MIX_VCO2_SAW,
    VCF_MOD1_KBD,
    VCF_MOD2_SH,
    VCF_ENV_ADSR,
    VCA_ENV_AR,
    ADSR_KBD_TRIGGER,
    ADSR_KBD_REPEAT,
    AR_KBD_TRIGGER,
};

enum class ControlType {
    BOOLEAN,
    FLOAT,
};

struct FloatControlValue {
    FloatControl control;
    float value;
};

struct BooleanControlValue {
    BooleanControl control;
    bool value;
};

union ControlValue {
    FloatControlValue float_cv;
    BooleanControlValue boolean_cv;
};

struct Control {
    ControlType type;
    ControlValue cv;
};

struct ControlNode : Control {
    bool applied, has_next, releasable;
    ControlNode* next;
};

class SynthController {
    Synth m_synth;

    ControlNode* control_head;
    ControlNode* control_reader;
    ControlNode* control_tail;
    void update_control(const Control& control);

public:
    SynthController();
    ~SynthController();
    inline const Synth& synth() const { return m_synth; }
    void push_control(const Control& control);
    void update();
};
