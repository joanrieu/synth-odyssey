////////////////////////////////////////////////////////////////////////////////
// HIGH-PASS FILTER
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

// in
extern unsigned
sr;
extern float
vcf_out;

// knobs
float
hpf_cutoff = 0;

// internal
float
hpf_sample = 0;

// out
float
hpf_out = 0;

void update_hpf() {
    auto rc = 1 / (2 * M_PI * hpf_cutoff);
    auto a = rc < INFINITY ? rc / (rc + 1.0 / sr) : 1;
    auto delta = vcf_out - hpf_sample;
    hpf_sample = vcf_out;
    hpf_out = a * (hpf_out + delta);
}
