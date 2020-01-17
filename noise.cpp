////////////////////////////////////////////////////////////////////////////////
// NOISE GENERATOR
////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include "coroutines.h"

// knobs
bool
noise_white = true;

// internal
// Trammel Stochastic Algorithm
// https://web.archive.org/web/20160705171002/http://home.earthlink.net/~ltrammell/tech/pinkalg.htm
static float noise_pink_band(float amplitude, float probability, float random) {
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
#define noise_pink_amp_1 (4.6306e-3)
#define noise_pink_amp_2 (5.9961e-3)
#define noise_pink_amp_3 (8.3586e-3)
#define noise_pink_amp_total (noise_pink_amp_1 + noise_pink_amp_2 + noise_pink_amp_3)
#define noise_pink_amp_1_norm (noise_pink_amp_1 / noise_pink_amp_total)
#define noise_pink_amp_2_norm (noise_pink_amp_2 / noise_pink_amp_total)
#define noise_pink_amp_3_norm (noise_pink_amp_3 / noise_pink_amp_total)
#define noise_pink_prob_1 (3.1878e-1)
#define noise_pink_prob_2 (7.7686e-1)
#define noise_pink_prob_3 (9.7785e-1)
#define noise_pink_band_1(x) noise_pink_band(noise_pink_amp_1_norm, noise_pink_prob_1, x)
#define noise_pink_band_2(x) noise_pink_band(noise_pink_amp_2_norm, noise_pink_prob_2, x)
#define noise_pink_band_3(x) noise_pink_band(noise_pink_amp_3_norm, noise_pink_prob_3, x)

// out
float
noise_out = 0;

void update_noise() {
    auto random = rand() / float(RAND_MAX);
    if (noise_white) {
        noise_out = random * 2 - 1;
    } else {
        noise_out = noise_pink_band_1(random) + noise_pink_band_2(random) + noise_pink_band_3(random);
    }
}
