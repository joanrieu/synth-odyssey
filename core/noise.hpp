#pragma once

struct Noise {
  // knobs
  bool white = true;

  // internal
  float samples[3] = {0};

  // out
  float out = 0;
};
