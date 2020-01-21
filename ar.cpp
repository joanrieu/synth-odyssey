////////////////////////////////////////////////////////////////////////////////
// ATTACK-RELEASE ENVELOPE
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

// in
extern unsigned
sr;
extern bool
adsr_kbd_repeat,
kbd_gate,
lfo_trigger,
kbd_trigger;

// knobs
float
ar_attack = 0,
ar_release = 0;
bool
ar_kbd_trigger = true;

// internal
float
ar_state = 0,
ar_done = 0,
ar_todo = 0;

// out
float
ar_out = 0;

// derived from update_adsr()
void update_ar() {
    auto auto_trigger = (adsr_kbd_repeat and kbd_gate and lfo_trigger) or (not adsr_kbd_repeat and lfo_trigger);
    auto trigger = (ar_kbd_trigger and kbd_trigger) or (not ar_kbd_trigger and auto_trigger);
    if (trigger) {
        ar_state = 1;
        ar_done = 0;
        ar_todo = std::floor(ar_attack * sr);
    }
    if (ar_state == 1) {
        if (ar_todo > 0) {
            ar_out = ar_done / (ar_done + ar_todo);
        } else {
            ar_state = 3;
        }
    }
    if (ar_state == 3) {
        ar_out = 1;
    }
    if ((ar_kbd_trigger and not kbd_gate and ar_state != 0 and ar_state != 4) or (not ar_kbd_trigger and ar_state == 3)) {
        ar_state = 4;
        ar_done = 0;
        ar_todo = std::floor(ar_release * sr);
    }
    if (ar_state == 4) {
        if (ar_todo > 0) {
            ar_out = ar_todo / (ar_done + ar_todo);
        } else {
            ar_state = 0;
        }
    }
    if (ar_state == 0) {
        ar_out = 0;
    } else {
        ar_done = ar_done + 1;
        ar_todo = ar_todo - 1;
    }
}
