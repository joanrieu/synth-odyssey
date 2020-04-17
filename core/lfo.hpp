#pragma once

struct LFO {
  // knobs
  float freq = 0;

  // internal
  float step = 0;

  // out
  float sine = 0;
  float square = 0;
  bool trigger = true;
};
