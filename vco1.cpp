////////////////////////////////////////////////////////////////////////////////
// VOLTAGE-CONTROLLED OSCILLATOR 1
////////////////////////////////////////////////////////////////////////////////

// in
extern unsigned
sr;
extern float
lfo_sine,
lfo_square,
sh_out,
adsr_out,
kbd_freq;

// knobs
float
vco1_tune = 0,
vco1_detune = 0,
vco1_fm1 = 0,
vco1_fm2 = 0,
vco1_pw = 0.5,
vco1_pwm = 0;
bool
vco1_kbd = true,
vco1_fm1_is_lfo_sine = true,
vco1_fm2_is_sh_out = true,
vco1_pwm_is_lfo = true;

// out
float
vco1_saw = 0,
vco1_square = 0;
bool
vco1_trigger = false;

void update_vco1() {
    vco1_trigger = false;
    auto fm =
        vco1_fm1 * (vco1_fm1_is_lfo_sine ? lfo_sine : lfo_square) +
        vco1_fm2 * (vco1_fm2_is_sh_out ? sh_out : adsr_out);
    auto freq = vco1_kbd ? kbd_freq : 1;
    auto step = 2 * freq * (vco1_tune + vco1_detune / 100 + fm) / sr;
    vco1_saw = vco1_saw + step;
    if (vco1_saw >= 1) {
        vco1_saw = -1;
        vco1_trigger = true;
    }
    auto pw_center =
        vco1_pw * 2 - 1 +
        vco1_pwm * (vco1_pwm_is_lfo ? lfo_sine : (adsr_out * 2 - 1));
    vco1_square = vco1_saw > pw_center ? 1 : -1;
}
