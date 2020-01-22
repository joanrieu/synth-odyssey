////////////////////////////////////////////////////////////////////////////////
// NOISE GENERATOR
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include "synth.hpp"

// Trammel Stochastic Algorithm
// https://web.archive.org/web/20160705171002/http://home.earthlink.net/~ltrammell/tech/pinkalg.htm

static const float amplitudes[] = { 0.00224, 0.00821, 0.00798, 0.00694, 0.00992 };
static const float probabilities[] = { 0.15571, 0.30194, 0.74115, 0.93003, 0.98035 };

static inline float random_float_positive() {
    return rand() / float(RAND_MAX);
}

static inline float random_float_signed() {
    return random_float_positive() * 2 - 1;
}

static inline float pink_band(Noise& noise, int i) {
    if (random_float_positive() < probabilities[i]) {
        noise.samples[i] = amplitudes[i] * random_float_signed() / 0.03529;
    }
    return noise.samples[i];
}

void Synth::update_noise() {
    if (noise.white) {
        noise.out = random_float_signed();
    } else {
        noise.out = pink_band(noise, 0) + pink_band(noise, 1) + pink_band(noise, 2);
    }
}
