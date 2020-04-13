#pragma once

#include <deque>

class CombFilter {
    std::deque<float> samples;
public:
    CombFilter(float delay, int sr);
    float update(float in);
};

class AllPassFilter {
    float g;
    std::deque<std::pair<float, float>> samples;
public:
    AllPassFilter(float gain, float delay, int sr);
    float update(float in);
};

struct Reverb {
    // knobs
    float cutoff = 0;

    // internal
    std::deque<CombFilter> combs;
    std::deque<AllPassFilter> allpasses;
    float lpf;

    // out
    float out;
};
