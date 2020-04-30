////////////////////////////////////////////////////////////////////////////////
// ATTACK-RELEASE ENVELOPE
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include "synth.hpp"

static constexpr auto epsilon = .001f;

void Synth::update_ar() {
  const bool trigger = ar.kbd_trigger ? kbd.trigger : lfo.trigger;
  const bool gate = adsr.kbd_repeat and kbd.gate;

  if (trigger) {
    if (ar.attack > epsilon or ar.release > epsilon)
      ar.phase = AR::ATTACK;
    else
      ar.phase = AR::RELEASE;
  }

  if (ar.phase == AR::ATTACK and ar.out > 1 - epsilon) {
    ar.phase = AR::SUSTAIN;
  }

  if (ar.phase == AR::SUSTAIN and not gate) {
    ar.phase = AR::RELEASE;
  }

  float target;
  float delay;

  switch (ar.phase) {
  case AR::ATTACK:
    target = 1;
    delay = ar.attack;
    break;
  case AR::SUSTAIN:
    target = 1;
    delay = 0;
    break;
  case AR::RELEASE:
    target = 0;
    delay = ar.release;
    break;
  }

  float coef = std::exp(-3 * M_LN2 / ((delay + epsilon) * sr));
  ar.out = coef * ar.out + (1 - coef) * target;
}
