#pragma once

struct SH {
    // knobs
    float
    vco1 = 0,
    noise = 0,
    lag = 0;
    bool
    vco1_saw = true,
    noise_gen = true,
    lfo_trigger = true;

    // internal
    float
    target = 0;

    // out
    float
    mix = 0,
    out = 0;
};
