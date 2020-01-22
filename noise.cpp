////////////////////////////////////////////////////////////////////////////////
// NOISE GENERATOR
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include "synth.hpp"

// Trammel Stochastic Algorithm
// https://web.archive.org/web/20160705171002/http://home.earthlink.net/~ltrammell/tech/pinkalg.htm
static float amplitudes[] = {
    0.24390449452997848,
    0.3158285620980443,
    0.4402669433719773
};
static float probabilities[] = {
    3.1878e-1,
    7.7686e-1,
    9.7785e-1
};
static float pink_band(int* state, float amplitude, float probability, float sample, float random) {
    crBegin(*state);
    while (true) {
        sample = amplitude * (random * 2 -1);
        do {
            crReturn(*state, sample);
        } while (random < probability);
    }
    crFinish();

    abort();
}

void Synth::update_noise() {
    auto random = rand() / float(RAND_MAX);
    if (noise.white) {
        noise.out = random * 2 - 1;
    } else {
        noise.out = 0;
        for (int i = 0; i < 3; ++i) {
            noise.out += noise.samples[i] = pink_band(
                &noise.state[i],
                amplitudes[i],
                probabilities[i],
                noise.samples[i],
                random
            );
        }
    }
}
