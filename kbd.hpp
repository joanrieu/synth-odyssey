#pragma once

struct Kbd {
    // knobs
    float
    portamento = 0,
    transpose = 0;
    bool
    sequencer = false;

    // internal
    float
    freq_target = 0;

    // out
    float
    freq = 0;
    bool
    trigger = false,
    gate = false;
};
