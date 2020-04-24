////////////////////////////////////////////////////////////////////////////////
// VOLTAGE-CONTROLLED FILTER
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cmath>

#include "synth.hpp"

static float error(const char *) { abort(); }

void Synth::update_vcf() {
  auto env1 =
      vcf.mod1 * (vcf.mod1_kbd ? error("VCF kbd mod unsupported") : sh.mix);
  auto env2 = vcf.mod2 * (vcf.mod2_sh ? sh.out : lfo.sine);
  auto env3 = vcf.env * (vcf.env_adsr ? adsr.out : ar.out);
  auto env =
      (env1 + env2 + env3) / std::max(1.f, vcf.mod1 + vcf.mod2 + vcf.env);
  auto cutoff = (1 + env / 2) * vcf.cutoff;

  // Non-Linear Digital Implementation of the Moog Ladder Filter
  // https://web.archive.org/web/20060501012842/http://dafx04.na.infn.it/WebProc/Proc/P_061.pdf

  constexpr float two_vt = 2 * 0.025; // Vt = 25mV
  auto g = 1 - std::exp(-2 * M_PI * cutoff / sr);

  for (int sample = 0; sample < 2; ++sample) {
    auto input_tanh = std::tanh((mix.out - 4 * vcf.reso * vcf.out) / two_vt);

    vcf.a = vcf.a + two_vt * g * (input_tanh - vcf.a_tanh);
    vcf.a_tanh = std::tanh(vcf.a / two_vt);

    vcf.b = vcf.b + two_vt * g * (vcf.a_tanh - vcf.b_tanh);
    vcf.b_tanh = std::tanh(vcf.b / two_vt);

    vcf.c = vcf.c + two_vt * g * (vcf.b_tanh - vcf.c_tanh);
    vcf.c_tanh = std::tanh(vcf.c / two_vt);

    auto old_d = vcf.d;
    vcf.d = vcf.d + two_vt * g * (vcf.c_tanh - vcf.d_tanh);
    vcf.d_tanh = std::tanh(vcf.d / two_vt);

    vcf.out = (vcf.d + old_d) / 2;
  }
}
