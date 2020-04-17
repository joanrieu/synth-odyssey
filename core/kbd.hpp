#pragma once

struct Kbd {
  // knobs
  float freq_target = 0;
  float portamento = 0;
  float transpose = 0;
  float pitch_bend = 0;

  // pass-through
  bool trigger = false;
  bool gate = false;

  // out
  float freq = 0;
};
