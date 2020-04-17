////////////////////////////////////////////////////////////////////////////////
// ATTACK-DECAY-SUSTAIN-RELEASE ENVELOPE
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include "synth.hpp"

void Synth::update_adsr() {
  auto auto_trigger = (adsr.kbd_repeat and kbd.gate and lfo.trigger) or
                      (not adsr.kbd_repeat and lfo.trigger);
  auto trigger = (adsr.kbd_trigger and kbd.trigger) or
                 (not adsr.kbd_trigger and auto_trigger);

  if (trigger) {
    adsr.phase = ADSR::ATTACK;
  }

  float target = adsr.phase == ADSR::RELEASE
                     ? 0
                     : adsr.phase == ADSR::DECAY ? adsr.sustain : 1;
  bool target_reached = std::abs(adsr.out - target) < 0.05;

  if (target_reached) {
    if (not adsr.kbd_trigger or not kbd.gate) {
      adsr.phase = ADSR::RELEASE;
      target = 0;
    } else if (adsr.phase == ADSR::ATTACK) {
      adsr.phase = ADSR::DECAY;
    }
  }

  float delay;

  switch (adsr.phase) {
  case ADSR::RELEASE:
    delay = adsr.release;
    break;
  case ADSR::DECAY:
    delay = adsr.decay;
    break;
  case ADSR::ATTACK:
    delay = adsr.attack;
    break;
  }

  float coef = std::exp(-3 * M_LN2 / ((delay + 0.01) * sr));
  adsr.out = coef * adsr.out + (1 - coef) * target;
}
