////////////////////////////////////////////////////////////////////////////////
// NOISE GENERATOR
////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include "coroutines.h"

#include "synth.hpp"

// Trammel Stochastic Algorithm
// https://web.archive.org/web/20160705171002/http://home.earthlink.net/~ltrammell/tech/pinkalg.htm
static float pink_band(float amplitude, float probability, float random) {
    static float sample;

    crBegin();
    while (true) {
        sample = amplitude * (random * 2 -1);
        do {
            crReturn(sample);
        } while (random < probability);
    }
    crFinish();

    abort();
}
#define pink_amp_1 (4.6306e-3)
#define pink_amp_2 (5.9961e-3)
#define pink_amp_3 (8.3586e-3)
#define pink_amp_total (pink_amp_1 + pink_amp_2 + pink_amp_3)
#define pink_amp_1_norm (pink_amp_1 / pink_amp_total)
#define pink_amp_2_norm (pink_amp_2 / pink_amp_total)
#define pink_amp_3_norm (pink_amp_3 / pink_amp_total)
#define pink_prob_1 (3.1878e-1)
#define pink_prob_2 (7.7686e-1)
#define pink_prob_3 (9.7785e-1)
#define pink_band_1(x) pink_band(pink_amp_1_norm, pink_prob_1, x)
#define pink_band_2(x) pink_band(pink_amp_2_norm, pink_prob_2, x)
#define pink_band_3(x) pink_band(pink_amp_3_norm, pink_prob_3, x)


void Synth::update_noise() {
    auto random = rand() / float(RAND_MAX);
    if (noise.white) {
        noise.out = random * 2 - 1;
    } else {
        noise.out = pink_band_1(random) + pink_band_2(random) + pink_band_3(random);
    }
}
