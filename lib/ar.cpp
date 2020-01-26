////////////////////////////////////////////////////////////////////////////////
// ATTACK-RELEASE ENVELOPE
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include "synth.hpp"

// derived from update_adsr()
void Synth::update_ar() {
    auto auto_trigger = (adsr.kbd_repeat and kbd.gate and lfo.trigger) or (not adsr.kbd_repeat and lfo.trigger);
    auto trigger = (ar.kbd_trigger and kbd.trigger) or (not ar.kbd_trigger and auto_trigger);
    if (trigger) {
        ar.state = 1;
        ar.done = 0;
        ar.todo = std::floor(ar.attack * sr);
    }
    if (ar.state == 1) {
        if (ar.todo > 0) {
            ar.out = ar.done / (ar.done + ar.todo);
        } else {
            ar.state = 3;
        }
    }
    if (ar.state == 3) {
        ar.out = 1;
    }
    if ((ar.kbd_trigger and not kbd.gate and ar.state != 0 and ar.state != 4) or (not ar.kbd_trigger and ar.state == 3)) {
        ar.state = 4;
        ar.done = 0;
        ar.todo = std::floor(ar.release * sr);
    }
    if (ar.state == 4) {
        if (ar.todo > 0) {
            ar.out = ar.todo / (ar.done + ar.todo);
        } else {
            ar.state = 0;
        }
    }
    if (ar.state == 0) {
        ar.out = 0;
    } else {
        ar.done = ar.done + 1;
        ar.todo = ar.todo - 1;
    }
}
