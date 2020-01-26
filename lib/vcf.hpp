#pragma once

#include <cmath>

struct VCF {
    // knobs
    float
    cutoff = INFINITY,
    reso = 0,
    mod1 = 0,
    mod2 = 0,
    env = 0;
    bool
    mod1_kbd = false,
    mod2_sh = true,
    env_adsr = true;

    // internal
    float
    _2vt = 2 * 0.025, // Vt = 25mV
    a = 0,
    a_tanh = 0,
    b = 0,
    b_tanh = 0,
    c = 0,
    c_tanh = 0,
    d = 0,
    d_tanh = 0;

    // out
    float
    out = 0;
};
