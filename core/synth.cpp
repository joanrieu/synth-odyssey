#include "synth.hpp"

float Synth::update() {
  update_kbd();
  update_ar();
  update_adsr();
  update_vco1();
  update_vco2();
  update_lfo();
  update_noise();
  update_sh();
  update_mix();
  update_vcf();
  update_hpf();
  update_vca();
  return vca.out;
}
