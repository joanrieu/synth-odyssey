#pragma once

struct AR {
    // knobs
    float
    attack = 0,
    release = 0;
    bool
    kbd_trigger = true;

    // internal
    enum Phase {
        ATTACK,
        RELEASE
    } phase = RELEASE;

    // out
    float
    out = 0;
};
