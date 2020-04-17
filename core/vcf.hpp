#pragma once

#include <cmath>

struct VCF {
  // knobs
  float cutoff = INFINITY;
  float reso = 0;
  float mod1 = 0;
  float mod2 = 0;
  float env = 0;
  bool mod1_kbd = false;
  bool mod2_sh = true;
  bool env_adsr = true;

  // internal
  float _2vt = 2 * 0.025; // Vt = 25mV
  float a = 0;
  float a_tanh = 0;
  float b = 0;
  float b_tanh = 0;
  float c = 0;
  float c_tanh = 0;
  float d = 0;
  float d_tanh = 0;

  // out
  float out = 0;
};
