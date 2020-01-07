--------------------------------------------------------------------------------
-- VOLTAGE-CONTROLLED OSCILLATOR 1
--------------------------------------------------------------------------------

-- knobs
vco1_tune = 0
vco1_detune = 0

-- out
vco1_saw = 0
vco1_square = 0
vco1_sync = false

function update_vco1()
    vco1_sync = false
    local step = 2 * kbd_freq * (vco1_tune + vco1_detune / 100) / sr
    vco1_saw = vco1_saw + step
    if vco1_saw >= 1 then
        vco1_saw = -1
        vco1_sync = true
    end
    vco1_square = vco1_saw > 0 and 1 or -1
end
