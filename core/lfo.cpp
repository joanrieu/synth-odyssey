////////////////////////////////////////////////////////////////////////////////
// LOW-FREQUENCY OSCILLATOR
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include "synth.hpp"

void Synth::update_lfo() {
  lfo.step = lfo.step + 1;
  auto steps = lfo.freq > 0 ? sr / lfo.freq : 0;
  if (lfo.step < steps) {
    lfo.sine = std::sin(2 * M_PI * lfo.step / steps);
    lfo.square = lfo.sine > 0 ? 1 : -1;
    lfo.trigger = false;
  } else {
    lfo.step = 0;
    lfo.sine = 0;
    lfo.square = 0;
    lfo.trigger = true;
  }
}
