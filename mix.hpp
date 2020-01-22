#pragma once

struct Mix {
    // knob
    float
    vco1 = 0,
    vco2 = 0,
    noise_ring = 0;
    bool
    vco1_saw = true,
    vco2_saw = true,
    noise = true;

    // out
    float
    out = 0;
};
