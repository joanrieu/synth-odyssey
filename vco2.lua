--------------------------------------------------------------------------------
-- VOLTAGE-CONTROLLED OSCILLATOR 2
--------------------------------------------------------------------------------

-- knobs
vco2_tune = 0
vco2_detune = 0
vco2_sync = false

-- out
vco2_saw = 0
vco2_square = 0

function update_vco2()
    if vco2_sync and vco1_sync then
        vco2_saw = -1
    else
        local step = 2 * kbd_freq * (vco2_tune + vco2_detune / 100) / sr
        vco2_saw = vco2_saw + step
        if vco2_saw >= 1 then
            vco2_saw = -1
        end
    end
    vco2_square = vco2_saw > 0 and 1 or -1
end
