////////////////////////////////////////////////////////////////////////////////
// KEYBOARD / SEQUENCER
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include "synth.hpp"

#define C3 130.8128
#define D3 146.8324
#define E3 164.8138
#define F3 174.6141
#define G3 195.9977
#define A3 220.0000
#define B3 246.9417
#define C4 261.6256
#define D4 293.6648

void Synth::update_kbd() {
    static int i, j;
    float a, transpose;
    float samples_per_note = 0.18 * sr;
    float melody[] = {
        A3, A3, A3, A3, A3, A3, A3, A3, A3, A3, A3, A3, A3, A3, A3, A3,
        F3, F3, F3, F3, F3, F3, F3, F3, F3, F3, F3, F3, F3, F3, F3, F3,
        D3, D3, D3, D3, D3, D3, D3, D3, D3, D3, D3, D3, D3, D3, D3, D3,
        D4, D4, D4, D4, D4, D4, D4, D4, D4, D4, D4, D4, D4, D4, D4, D4,
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
