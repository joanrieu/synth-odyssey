////////////////////////////////////////////////////////////////////////////////
// VOLTAGE-CONTROLLED FILTER
////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <algorithm>

// in
extern float
sr,
sh_mix,
sh_out,
lfo_sine,
adsr_out,
ar_out,
mix_out;

// knobs
float
vcf_cutoff = INFINITY,
vcf_reso = 0,
vcf_mod1 = 0,
vcf_mod2 = 0,
vcf_env = 0;
bool
vcf_mod1_kbd = false,
vcf_mod2_sh = true,
vcf_env_adsr = true;

// internal
float
vcf_2vt = 2 * 0.025, // Vt = 25mV
vcf_a = 0,
vcf_a_tanh = 0,
vcf_b = 0,
vcf_b_tanh = 0,
vcf_c = 0,
vcf_c_tanh = 0,
vcf_d = 0,
vcf_d_tanh = 0;

// out
float
vcf_out = 0;

static float error(const char*) { abort(); }

void update_vcf() {
    auto env1 = vcf_mod1 * (vcf_mod1_kbd ? error("VCF kbd mod unsupported") : sh_mix);
    auto env2 = vcf_mod2 * (vcf_mod2_sh ? sh_out : lfo_sine);
    auto env3 = vcf_env * (vcf_env_adsr ? adsr_out : ar_out);
    auto env = (env1 + env2 + env3) / std::max(1.f, vcf_mod1 + vcf_mod2 + vcf_env);
    auto cutoff = (env + (1 - vcf_env)) * vcf_cutoff;

    // Non-Linear Digital Implementation of the Moog Ladder Filter
    // https://web.archive.org/web/20060501012842/http://dafx04.na.infn.it/WebProc/Proc/P_061.pdf
    auto g = 1 - std::exp(-2 * M_PI * cutoff / sr);
    auto x = mix_out - 4 * vcf_reso * vcf_out;
    vcf_a_tanh = std::tanh(vcf_a / vcf_2vt);
    vcf_a = vcf_a + vcf_2vt * g * (std::tanh(x / vcf_2vt) - vcf_a_tanh);
    vcf_b_tanh = std::tanh(vcf_b / vcf_2vt);
    vcf_b = vcf_b + vcf_2vt * g * (vcf_a_tanh - vcf_b_tanh);
    vcf_c_tanh = std::tanh(vcf_c / vcf_2vt);
    vcf_c = vcf_c + vcf_2vt * g * (vcf_b_tanh - vcf_c_tanh);
    vcf_d_tanh = std::tanh(vcf_out / vcf_2vt);
    vcf_d = vcf_out + vcf_2vt * g * (vcf_c_tanh - vcf_d_tanh);

    vcf_out = vcf_d;
}
