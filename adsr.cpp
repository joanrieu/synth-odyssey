////////////////////////////////////////////////////////////////////////////////
// ATTACK-DECAY-SUSTAIN-RELEASE ENVELOPE
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

// in
extern unsigned
sr;
extern bool
kbd_gate,
lfo_trigger,
kbd_trigger;

// knobs
float
adsr_attack = 0,
adsr_sustain = 0,
adsr_decay = 0,
adsr_release = 0;
bool
adsr_kbd_trigger = true,
adsr_kbd_repeat = true;

// internal
float
adsr_state = 0,
adsr_done = 0,
adsr_todo = 0;

// out
float
adsr_out = 0;

void update_adsr() {
    auto auto_trigger = (adsr_kbd_repeat and kbd_gate and lfo_trigger) or (not adsr_kbd_repeat and lfo_trigger);
    auto trigger = (adsr_kbd_trigger and kbd_trigger) or (not adsr_kbd_trigger and auto_trigger);
    if (trigger) {
        adsr_state = 1;
        adsr_done = 0;
        adsr_todo = std::floor(adsr_attack * sr);
    }
    if (adsr_state == 1) {
        if (adsr_todo > 0) {
            adsr_out = adsr_done / (adsr_done + adsr_todo);
        } else {
            adsr_state = 2;
            adsr_done = 0;
            adsr_todo = std::floor(adsr_decay * sr);
        }
    }
    if (adsr_state == 2) {
        if (adsr_todo > 0) {
            adsr_out = 1 - ((1 - adsr_sustain) * adsr_done / (adsr_done + adsr_todo));
        } else {
            adsr_state = 3;
        }
    }
    if (adsr_state == 3) {
        adsr_out = adsr_sustain;
    }
    if ((adsr_kbd_trigger and not kbd_gate and adsr_state != 0 and adsr_state != 4) or (not adsr_kbd_trigger and adsr_state == 3)) {
        adsr_state = 4;
        adsr_done = 0;
        adsr_todo = std::floor(adsr_release * sr);
    }
    if (adsr_state == 4) {
        if (adsr_todo > 0) {
            adsr_out = adsr_sustain * adsr_todo / (adsr_done + adsr_todo);
        } else {
            adsr_state = 0;
        }
    }
    if (adsr_state == 0) {
        adsr_out = 0;
    } else {
        adsr_done = adsr_done + 1;
        adsr_todo = adsr_todo - 1;
    }
}
