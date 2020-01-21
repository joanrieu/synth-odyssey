////////////////////////////////////////////////////////////////////////////////
// LOW-FREQUENCY OSCILLATOR
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

// in
extern unsigned
sr;

// knobs
float
lfo_freq = 0;

// internal
float
lfo_step = 0;

// out
float
lfo_sine = 0,
lfo_square = 0;
bool
lfo_trigger = true;

void update_lfo() {
    lfo_step = lfo_step + 1;
    auto steps = lfo_freq > 0 ? sr / lfo_freq : 0;
    if (lfo_step < steps) {
        lfo_sine = std::sin(2 * M_PI * lfo_step / steps);
        lfo_square = lfo_sine > 0 ? 1 : -1;
        lfo_trigger = false;
    } else {
        lfo_step = 0;
        lfo_sine = 0;
        lfo_square = 0;
        lfo_trigger = true;
    }
}
