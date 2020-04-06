#pragma once

#include "adsr.hpp"
#include "ar.hpp"
#include "hpf.hpp"
#include "kbd.hpp"
#include "lfo.hpp"
#include "mix.hpp"
#include "noise.hpp"
#include "sh.hpp"
#include "vca.hpp"
#include "vcf.hpp"
#include "vco1.hpp"
#include "vco2.hpp"

class Synth {
    void update_adsr();
    void update_ar();
    void update_hpf();
    void update_kbd();
    void update_lfo();
    void update_mix();
    void update_noise();
    void update_sh();
    void update_vca();
    void update_vcf();
    void update_vco1();
    void update_vco2();

protected:
    ADSR adsr;
    AR ar;
    HPF hpf;
    Kbd kbd;
    LFO lfo;
    Mix mix;
    Noise noise;
    SH sh;
    VCA vca;
    VCF vcf;
    VCO1 vco1;
    VCO2 vco2;

public:
    virtual ~Synth() {}
    virtual float update();

    unsigned sr = 44100;
};
