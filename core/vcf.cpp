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
  auto cutoff = (env + (1 - vcf.env)) * vcf.cutoff;

  // Non-Linear Digital Implementation of the Moog Ladder Filter
  // https://web.archive.org/web/20060501012842/http://dafx04.na.infn.it/WebProc/Proc/P_061.pdf
  auto g = 1 - std::exp(-2 * M_PI * cutoff / sr);
  auto x = mix.out - 4 * vcf.reso * vcf.out;
  vcf.a_tanh = std::tanh(vcf.a / vcf._2vt);
  vcf.a = vcf.a + vcf._2vt * g * (std::tanh(x / vcf._2vt) - vcf.a_tanh);
  vcf.b_tanh = std::tanh(vcf.b / vcf._2vt);
  vcf.b = vcf.b + vcf._2vt * g * (vcf.a_tanh - vcf.b_tanh);
  vcf.c_tanh = std::tanh(vcf.c / vcf._2vt);
  vcf.c = vcf.c + vcf._2vt * g * (vcf.b_tanh - vcf.c_tanh);
  vcf.d_tanh = std::tanh(vcf.out / vcf._2vt);
  vcf.d = vcf.out + vcf._2vt * g * (vcf.c_tanh - vcf.d_tanh);

  vcf.out = vcf.d;
}
