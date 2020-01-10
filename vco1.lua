--------------------------------------------------------------------------------
-- VOLTAGE-CONTROLLED OSCILLATOR 1
--------------------------------------------------------------------------------

-- knobs
vco1_tune = 0
vco1_detune = 0
vco1_kbd = true
vco1_fm1 = 0
vco1_fm1_is_lfo_sine = true
vco1_fm2 = 0
vco1_fm2_is_sh_out = true
vco1_pw = 0.5
vco1_pwm = 0
vco1_pwm_is_lfo = true

-- out
vco1_saw = 0
vco1_square = 0
vco1_sync = false

function update_vco1()
    vco1_sync = false
    local fm =
        vco1_fm1 * (vco1_fm1_is_lfo_sine and lfo_sine or lfo_square) +
        vco1_fm2 * (vco1_fm2_is_sh_out and sh_out or adsr_out)
    local freq = vco1_kbd and kbd_freq or 1
    local step = 2 * freq * (vco1_tune + vco1_detune / 100 + fm) / sr
    vco1_saw = vco1_saw + step
    if vco1_saw >= 1 then
        vco1_saw = -1
        vco1_sync = true
    end
    local pw_center =
        vco1_pw * 2 - 1 +
        vco1_pwm * (vco1_pwm_is_lfo and lfo_sine or (adsr_out * 2 - 1))
    vco1_square = vco1_saw > pw_center and 1 or -1
end
