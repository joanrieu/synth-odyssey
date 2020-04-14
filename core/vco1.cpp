////////////////////////////////////////////////////////////////////////////////
// VOLTAGE-CONTROLLED OSCILLATOR 1
////////////////////////////////////////////////////////////////////////////////

#include "synth.hpp"

void Synth::update_vco1() {
    vco1.trigger = false;
    auto fm =
        vco1.fm1 * (vco1.fm1_is_lfo_sine ? lfo.sine : lfo.square) +
        vco1.fm2 * (vco1.fm2_is_sh_out ? sh.out : adsr.out);
    auto freq = vco1.kbd ? kbd.freq : 1;
    auto step = 2 * freq * vco1.tune * (1 + vco1.detune + kbd.pitch_bend + fm / 2) / sr;
    vco1.saw = vco1.saw + step;
    if (vco1.saw >= 1) {
        vco1.saw = -1;
        vco1.trigger = true;
    }
    auto pw_center =
        vco1.pw * 2 - 1 +
        vco1.pwm * (vco1.pwm_is_lfo ? lfo.sine : (adsr.out * 2 - 1));
    vco1.square = vco1.saw > pw_center ? 1 : -1;
}
