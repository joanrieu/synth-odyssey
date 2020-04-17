////////////////////////////////////////////////////////////////////////////////
// VOLTAGE-CONTROLLED OSCILLATOR 2
////////////////////////////////////////////////////////////////////////////////

#include "synth.hpp"

void Synth::update_vco2() {
  if (vco2.sync and vco1.trigger) {
    vco2.saw = -1;
  } else {
    auto fm = vco2.fm1 * (vco2.fm1_is_lfo_sine ? lfo.sine : sh.mix) +
              vco2.fm2 * (vco2.fm2_is_sh_out ? sh.out : adsr.out);
    auto step = 2 * kbd.freq * vco2.tune *
                (1 + vco2.detune + kbd.pitch_bend + fm / 2) / sr;
    vco2.saw = vco2.saw + step;
    if (vco2.saw >= 1) {
      vco2.saw = -1;
    }
  }
  auto pw_center = vco2.pw * 2 - 1 +
                   vco2.pwm * (vco2.pwm_is_lfo ? lfo.sine : (adsr.out * 2 - 1));
  vco2.square = vco2.saw > pw_center ? 1 : -1;
}
