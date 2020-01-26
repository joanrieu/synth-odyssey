////////////////////////////////////////////////////////////////////////////////
// ATTACK-DECAY-SUSTAIN-RELEASE ENVELOPE
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include "synth.hpp"

void Synth::update_adsr() {
    auto auto_trigger = (adsr.kbd_repeat and kbd.gate and lfo.trigger) or (not adsr.kbd_repeat and lfo.trigger);
    auto trigger = (adsr.kbd_trigger and kbd.trigger) or (not adsr.kbd_trigger and auto_trigger);
    if (trigger) {
        adsr.state = 1;
        adsr.done = 0;
        adsr.todo = std::floor(adsr.attack * sr);
    }
    if (adsr.state == 1) {
        if (adsr.todo > 0) {
            adsr.out = adsr.done / (adsr.done + adsr.todo);
        } else {
            adsr.state = 2;
            adsr.done = 0;
            adsr.todo = std::floor(adsr.decay * sr);
        }
    }
    if (adsr.state == 2) {
        if (adsr.todo > 0) {
            adsr.out = 1 - ((1 - adsr.sustain) * adsr.done / (adsr.done + adsr.todo));
        } else {
            adsr.state = 3;
        }
    }
    if (adsr.state == 3) {
        adsr.out = adsr.sustain;
    }
    if ((adsr.kbd_trigger and not kbd.gate and adsr.state != 0 and adsr.state != 4) or (not adsr.kbd_trigger and adsr.state == 3)) {
        adsr.state = 4;
        adsr.done = 0;
        adsr.todo = std::floor(adsr.release * sr);
    }
    if (adsr.state == 4) {
        if (adsr.todo > 0) {
            adsr.out = adsr.sustain * adsr.todo / (adsr.done + adsr.todo);
        } else {
            adsr.state = 0;
        }
    }
    if (adsr.state == 0) {
        adsr.out = 0;
    } else {
        adsr.done = adsr.done + 1;
        adsr.todo = adsr.todo - 1;
    }
}
