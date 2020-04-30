#pragma once

struct ADSR {
  // knobs
  float attack = 0;
  float decay = 0;
  float sustain = 0;
  float release = 0;
  bool kbd_trigger = true;
  bool kbd_repeat = true;

  // internal
  enum Phase { ATTACK, DECAY_AND_SUSTAIN, RELEASE } phase = RELEASE;

  // out
  float out = 0;
};
