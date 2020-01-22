#pragma once

struct VCO2 {
    // knobs
    float
    tune = 0,
    detune = 0,
    fm1 = 0,
    fm2 = 0,
    pw = 0.5,
    pwm = 0;
    bool
    sync = false,
    fm1_is_lfo_sine = true,
    fm2_is_sh_out = true,
    pwm_is_lfo = true;

    // out
    float
    saw = 0,
    square = 0;
};
