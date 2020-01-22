////////////////////////////////////////////////////////////////////////////////
// SAMPLE / HOLD
////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <algorithm>

#include "synth.hpp"

void Synth::update_sh() {
    auto vco1_wave = sh.vco1 * (sh.vco1_saw ? vco1.saw : vco1.square);
    auto noise_vco2 = sh.noise * (sh.noise_gen ? noise.out : vco2.square);
    sh.mix = (vco1_wave + noise_vco2) / std::max(1.f, sh.vco1 + sh.noise);
    auto trigger = sh.lfo_trigger ? lfo.trigger : kbd.trigger;
    if (trigger) {
        sh.target = sh.mix;
    }
    auto a = 1 - std::pow(10, -2 - sh.lag * sr / 2e4);
    sh.out = a * sh.out + (1 - a) * sh.target;
}
