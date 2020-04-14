#pragma once

struct Kbd {
    // knobs
    float
    freq_target = 0,
    portamento = 0,
    transpose = 0,
    pitch_bend = 0;

    // pass-through
    bool
    trigger = false,
    gate = false;

    // out
    float
    freq = 0;
};
