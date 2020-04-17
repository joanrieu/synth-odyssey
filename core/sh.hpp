#pragma once

struct SH {
  // knobs
  float vco1 = 0;
  float noise = 0;
  float lag = 0;
  bool vco1_saw = true;
  bool noise_gen = true;
  bool lfo_trigger = true;

  // internal
  float target = 0;

  // out
  float mix = 0;
  float out = 0;
};
