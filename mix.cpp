////////////////////////////////////////////////////////////////////////////////
// MIXER
////////////////////////////////////////////////////////////////////////////////

#include "synth.hpp"

void Synth::update_mix() {
    auto vco1_wave = mix.vco1_saw ? vco1.saw : vco1.square;
    auto vco2_wave = mix.vco2_saw ? vco2.saw : vco2.square;
    auto noise_ring = mix.noise ? noise.out : vco1_wave * vco2_wave;
    mix.out = mix.vco1 * vco1_wave + mix.vco2 * vco2_wave + mix.noise_ring * noise_ring;
}
