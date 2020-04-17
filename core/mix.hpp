#pragma once

struct Mix {
  // knob
  float vco1 = 0;
  float vco2 = 0;
  float noise_ring = 0;
  bool vco1_saw = true;
  bool vco2_saw = true;
  bool noise = true;

  // out
  float out = 0;
};
