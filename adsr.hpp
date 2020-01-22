#pragma once

struct ADSR {
    // knobs
    float
    attack = 0,
    sustain = 0,
    decay = 0,
    release = 0;
    bool
    kbd_trigger = true,
    kbd_repeat = true;

    // internal
    float
    state = 0,
    done = 0,
    todo = 0;

    // out
    float
    out = 0;
};
