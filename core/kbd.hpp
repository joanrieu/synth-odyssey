#pragma once

#include "coroutines.hpp"

struct Kbd {
    // knobs
    float
    portamento = 0,
    transpose = 0;
    bool
    sequencer = false;

    // internal
    int
    state = 0;
    float
    freq_target = 0;

    // out
    float
    freq = 0;
    bool
    trigger = false,
    gate = false;
};
