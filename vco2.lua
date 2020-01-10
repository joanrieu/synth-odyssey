--------------------------------------------------------------------------------
-- VOLTAGE-CONTROLLED OSCILLATOR 2
--------------------------------------------------------------------------------

-- knobs
vco2_tune = 0
vco2_detune = 0
vco2_sync = false
vco2_fm1 = 0
vco2_fm1_is_lfo_sine = true
vco2_fm2 = 0
vco2_fm2_is_sh_out = true
vco2_pw = 0.5

-- out
vco2_saw = 0
vco2_square = 0

function update_vco2()
    if vco2_sync and vco1_sync then
        vco2_saw = -1
    else
        local fm =
            vco2_fm1 * (vco2_fm1_is_lfo_sine and lfo_sine or sh_mix) +
            vco2_fm2 * (vco2_fm2_is_sh_out and sh_out or adsr_out)
        local step = 2 * kbd_freq * (vco2_tune + vco2_detune / 100 + fm) / sr
        vco2_saw = vco2_saw + step
        if vco2_saw >= 1 then
            vco2_saw = -1
        end
    end
    vco2_square = vco2_saw > vco2_pw * 2 - 1 and 1 or -1
end
