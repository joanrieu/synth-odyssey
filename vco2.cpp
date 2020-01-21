////////////////////////////////////////////////////////////////////////////////
// VOLTAGE-CONTROLLED OSCILLATOR 2
////////////////////////////////////////////////////////////////////////////////

// in
extern unsigned
sr;
extern float
lfo_sine,
sh_mix,
sh_out,
adsr_out,
kbd_freq;
extern bool
vco1_trigger;

// knobs
float
vco2_tune = 0,
vco2_detune = 0,
vco2_fm1 = 0,
vco2_fm2 = 0,
vco2_pw = 0.5,
vco2_pwm = 0;
bool
vco2_sync = false,
vco2_fm1_is_lfo_sine = true,
vco2_fm2_is_sh_out = true,
vco2_pwm_is_lfo = true;

// out
float
vco2_saw = 0,
vco2_square = 0;

void update_vco2() {
    if (vco2_sync and vco1_trigger) {
        vco2_saw = -1;
    } else {
        auto fm =
            vco2_fm1 * (vco2_fm1_is_lfo_sine ? lfo_sine : sh_mix) +
            vco2_fm2 * (vco2_fm2_is_sh_out ? sh_out : adsr_out);
        auto step = 2 * kbd_freq * (vco2_tune + vco2_detune / 100 + fm) / sr;
        vco2_saw = vco2_saw + step;
        if (vco2_saw >= 1) {
            vco2_saw = -1;
        }
    }
    auto pw_center =
        vco2_pw * 2 - 1 +
        vco2_pwm * (vco2_pwm_is_lfo ? lfo_sine : (adsr_out * 2 - 1));
    vco2_square = vco2_saw > pw_center ? 1 : -1;
}
