////////////////////////////////////////////////////////////////////////////////
// HIGH-PASS FILTER
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include "synth.hpp"

void Synth::update_hpf() {
    auto rc = 1 / (2 * M_PI * hpf.cutoff);
    auto a = rc < INFINITY ? rc / (rc + 1.0 / sr) : 1;
    auto delta = vcf.out - hpf.sample;
    hpf.sample = vcf.out;
    hpf.out = a * (hpf.out + delta);
}
