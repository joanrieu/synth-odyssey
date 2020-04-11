#pragma once

struct ADSR {
    // knobs
    float
    attack = 0,
    decay = 0,
    sustain = 0,
    release = 0;
    bool
    kbd_trigger = true,
    kbd_repeat = true;

    // internal
    enum Phase {
        ATTACK,
        DECAY,
        RELEASE
    } phase = RELEASE;

    // out
    float
    out = 0;
};
