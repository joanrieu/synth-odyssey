#pragma once

struct VCO2 {
  // knobs
  float tune = 0;
  float detune = 0;
  float fm1 = 0;
  float fm2 = 0;
  float pw = 0.5;
  float pwm = 0;
  bool sync = false;
  bool fm1_is_lfo_sine = true;
  bool fm2_is_sh_out = true;
  bool pwm_is_lfo = true;

  // out
  float saw = 0;
  float square = 0;
};
