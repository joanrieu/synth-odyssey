////////////////////////////////////////////////////////////////////////////////
// ATTACK-DECAY-SUSTAIN-RELEASE ENVELOPE
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include "synth.hpp"

static constexpr auto epsilon = .001f;

void Synth::update_adsr() {
  const bool trigger = adsr.kbd_trigger ? kbd.trigger : lfo.trigger;
  const bool gate = adsr.kbd_repeat and kbd.gate;

  if (trigger) {
    if (adsr.attack > epsilon or adsr.decay > epsilon)
      adsr.phase = ADSR::ATTACK;
    else
      adsr.phase = ADSR::DECAY_AND_SUSTAIN;
  }

  if (adsr.phase == ADSR::ATTACK and adsr.out > 1 - epsilon) {
    adsr.phase = ADSR::DECAY_AND_SUSTAIN;
  }

  if (adsr.phase == ADSR::DECAY_AND_SUSTAIN and
      std::abs(adsr.out - adsr.sustain) < epsilon and not gate) {
    adsr.phase = ADSR::RELEASE;
  }

  float target;
  float delay;

  switch (adsr.phase) {
  case ADSR::ATTACK:
    target = 1;
    delay = adsr.attack;
    break;
  case ADSR::DECAY_AND_SUSTAIN:
    target = adsr.sustain;
    delay = adsr.decay;
    break;
  case ADSR::RELEASE:
    target = 0;
    delay = adsr.release;
    break;
  }

  float coef = std::exp(-3 * M_LN2 / ((delay + epsilon) * sr));
  adsr.out = coef * adsr.out + (1 - coef) * target;
}
