////////////////////////////////////////////////////////////////////////////////
// KEYBOARD / SEQUENCER
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include "synth.hpp"

void Synth::update_kbd() {
  float a = 1 - std::pow(10, -2 - kbd.portamento * sr / 2e4);
  kbd.freq =
      a * kbd.freq + (1 - a) * kbd.freq_target * std::pow(2, kbd.transpose);
}
