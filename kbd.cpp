////////////////////////////////////////////////////////////////////////////////
// KEYBOARD / SEQUENCER
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include "synth.hpp"

void Synth::update_kbd() {
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
    
    crBegin(kbd.state);
    while (true) {
        for (i = 0; melody[i]; ++i) {
            for (j = 0; j < samples_per_note; ++j) {
                if (kbd.sequencer) {
                    kbd.trigger = j == 0;
                    kbd.gate = j < samples_per_note;
                    kbd.freq_target = melody[i];
                }
                a = 1 - std::pow(10, -2 - kbd.portamento * sr / 2e4);
                transpose = kbd.transpose >= 0 ? std::pow(2, kbd.transpose) : 1 / std::pow(2, -kbd.transpose);
                kbd.freq = a * kbd.freq + (1 - a) * kbd.freq_target * transpose;
                crReturn(kbd.state, /* void */);
            }
        }
    }
    crFinish();
}
