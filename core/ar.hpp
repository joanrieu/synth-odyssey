#pragma once

struct AR {
    // knobs
    float
    attack = 0,
    release = 0;
    bool
    kbd_trigger = true;

    // internal
    float
    state = 0,
    done = 0,
    todo = 0;

    // out
    float
    out = 0;
};
