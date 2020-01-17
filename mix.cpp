////////////////////////////////////////////////////////////////////////////////
// MIXER
////////////////////////////////////////////////////////////////////////////////

// in
extern float
vco1_saw,
vco1_square,
vco2_saw,
vco2_square,
noise_out;

// knob
float
mix_vco1 = 0,
mix_vco2 = 0,
mix_noise_ring = 0;
bool
mix_vco1_saw = true,
mix_vco2_saw = true,
mix_noise = true;

// out
float
mix_out = 0;

void update_mix() {
    auto vco1 = mix_vco1_saw ? vco1_saw : vco1_square;
    auto vco2 = mix_vco2_saw ? vco2_saw : vco2_square;
    auto noise_ring = mix_noise ? noise_out : vco1 * vco2;
    mix_out = mix_vco1 * vco1 + mix_vco2 * vco2 + mix_noise_ring * noise_ring;
}
