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
        ar.phase = AR::ATTACK;
    }

    float target = ar.phase == AR::RELEASE ? 0 : 1;
    bool target_reached = std::abs(ar.out - target) < 0.05;

    if (target_reached) {
        if (not ar.kbd_trigger or not kbd.gate) {
            ar.phase = AR::RELEASE;
            target = 0;
        }
    }

    float delay;

    switch (ar.phase) {
    case AR::RELEASE:
        delay = ar.release;
        break;
    case AR::ATTACK:
        delay = ar.attack;
        break;
    }

    float coef = std::exp(-3 * M_LN2 / ((delay + 0.01) * sr));
    ar.out = coef * ar.out + (1 - coef) * target;
}
