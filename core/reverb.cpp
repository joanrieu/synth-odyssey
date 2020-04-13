#include "synth.hpp"

CombFilter::CombFilter(float delay, int sr) {
    samples.resize(delay * sr);
}

float CombFilter::update(float in) {
    auto &out_d = samples.back();
    float a = 0.7;
    float out =  in + a * out_d;
    samples.pop_back();
    samples.push_front(out);
    return out;
}

AllPassFilter::AllPassFilter(float gain, float delay, int sr) : g(gain) {
    samples.resize(delay * sr);
}

float AllPassFilter::update(float in) {
    auto &tail = samples.back();
    auto &in_d = tail.first;
    auto &out_d = tail.second;
    float a = 0.7;
    float out = g * (a * in - in_d) + a * out_d;
    samples.pop_back();
    samples.push_front(std::make_pair(in, out));
    return out;
}

void Synth::update_reverb() {
    if (reverb.combs.empty()) {
        reverb.combs = {
            CombFilter(.01, sr),
            CombFilter(.12, sr),
            CombFilter(.23, sr),
            CombFilter(.34, sr),
            CombFilter(.45, sr),
            CombFilter(.56, sr),
        };
        reverb.allpasses = {
            AllPassFilter(.3, .012, sr),
            AllPassFilter(.3, .023, sr),
        };
    }

    // A Brief Overview of Reverberation Algorithms
    // http://freeverb3vst.osdn.jp/doc/A%20Brief%20Overview%20of%20Algorithm%20of%20Reverberation.pdf

    float &in = vca.out;
    float r = reverb.allpasses[1].update(
        reverb.allpasses[0].update(
            reverb.combs[0].update(in) +
            reverb.combs[1].update(in) +
            reverb.combs[2].update(in) +
            reverb.combs[3].update(in) +
            reverb.combs[4].update(in) +
            reverb.combs[5].update(in)
        )
    );

    // Simple infinite impulse response filter
    // https://en.wikipedia.org/wiki/Low-pass_filter#Simple_infinite_impulse_response_filter

    float a = 2 * M_PI * reverb.cutoff / sr;
    a = a / (a + 1);
    reverb.lpf = (1 - a) * reverb.lpf + a * r;
    reverb.lpf = (1 - a) * reverb.lpf + a * r;
    reverb.out = in + reverb.lpf;
}
