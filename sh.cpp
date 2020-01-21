////////////////////////////////////////////////////////////////////////////////
// SAMPLE / HOLD
////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <algorithm>

// in
extern unsigned
sr;
extern float
vco1_saw,
vco1_square,
noise_out,
vco2_square;
extern bool
lfo_trigger,
kbd_trigger;

// knobs
float
sh_vco1 = 0,
sh_noise = 0,
sh_lag = 0;
bool
sh_vco1_saw = true,
sh_noise_gen = true,
sh_lfo_trigger = true;

// internal
float
sh_target = 0;

// out
float
sh_mix = 0,
sh_out = 0;

void update_sh() {
    auto vco1 = sh_vco1 * (sh_vco1_saw ? vco1_saw : vco1_square);
    auto noise_vco2 = sh_noise * (sh_noise_gen ? noise_out : vco2_square);
    sh_mix = (vco1 + noise_vco2) / std::max(1.f, sh_vco1 + sh_noise);
    auto trigger = sh_lfo_trigger ? lfo_trigger : kbd_trigger;
    if (trigger) {
        sh_target = sh_mix;
    }
    auto a = 1 - std::pow(10, -2 - sh_lag * sr / 2e4);
    sh_out = a * sh_out + (1 - a) * sh_target;
}
