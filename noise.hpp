#pragma once

#include "coroutines.hpp"

struct Noise {
    // knobs
    bool
    white = true;

    // internal
    int
    state[3] = {0};
    float
    samples[3] = {0};

    // out
    float
    out = 0;
};
