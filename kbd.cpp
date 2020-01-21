////////////////////////////////////////////////////////////////////////////////
// KEYBOARD / SEQUENCER
////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include "coroutines.h"

// in
extern unsigned
sr;

// knobs
float
kbd_portamento = 0,
kbd_transpose = 0;
bool
kbd_sequencer = false;

// internal
float
kbd_freq_target = 0;

// out
float
kbd_freq = 0;
bool
kbd_trigger = false,
kbd_gate = false;

void update_kbd() {
    static int i, j;
    float a, transpose;
    
    float D2 = 73.42;
    float A1 = 55.00;
    float F1 = 43.65;
    float D1 = 36.71;
    float samples_per_note = 0.18 * sr;
    float melody[] = {
        A1, A1, A1, A1, A1, A1, A1, A1, A1, A1, A1, A1, A1, A1, A1, A1,
        F1, F1, F1, F1, F1, F1, F1, F1, F1, F1, F1, F1, F1, F1, F1, F1,
        D1, D1, D1, D1, D1, D1, D1, D1, D1, D1, D1, D1, D1, D1, D1, D1,
        D2, D2, D2, D2, D2, D2, D2, D2, D2, D2, D2, D2, D2, D2, D2, D2,
        0
    };
    
    crBegin();
    while (true) {
        for (i = 0; melody[i]; ++i) {
            for (j = 0; j < samples_per_note; ++j) {
                if (kbd_sequencer) {
                    kbd_trigger = j == 0;
                    kbd_gate = j < samples_per_note;
                    kbd_freq_target = melody[i];
                }
                a = 1 - std::pow(10, -2 - kbd_portamento * sr / 2e4);
                transpose = kbd_transpose >= 0 ? std::pow(2, kbd_transpose) : 1 / std::pow(2, -kbd_transpose);
                kbd_freq = a * kbd_freq + (1 - a) * kbd_freq_target * transpose;
                crReturn();
            }
        }
    }
    crFinish();
}
