-- global
sr = 44100
cv_to_hz = 440.0 / 8.0

-- KBD out
kbd_gate = 0.0
kbd_cv = 0.0

-- VCO 1 knobs
vco1_tune = 1.0
vco1_detune = 0.0

-- VCO 1 out
vco1_saw = 0.0
vco1_square = 0.0

-- VCO 2 knobs
vco2_tune = 1.0
vco2_detune = 0.0

-- VCO 2 out
vco2_saw = 0.0
vco2_square = 0.0

-- MIX out
mix_out = 0.0

-- VCA knobs
vca_gain = 0.0

-- VCA out
vca_out = 0.0

function update()
    -- VCO 1
    if kbd_gate > 1 then
        local step = 2 * kbd_cv * cv_to_hz * (vco1_tune + vco1_detune / 100) / sr
        vco1_saw = vco1_saw + step
        if vco1_saw >= 1 then
            vco1_saw = -1
        end
        if vco1_saw > 0 then
            vco1_square = 1
        else
            vco1_square = -1
        end
    else
        vco1_saw = 0
    end

    -- VCO 2
    if kbd_gate > 1 then
        local step = 2 * kbd_cv * cv_to_hz * (vco2_tune + vco2_detune / 100) / sr
        vco2_saw = vco2_saw + step
        if vco2_saw >= 1 then
            vco2_saw = -1
        end
        if vco2_saw > 0 then
            vco2_square = 1
        else
            vco2_square = -1
        end
    else
        vco2_saw = 0
    end

    -- MIX
    mix_out = (vco1_saw + vco2_saw) / 2

    -- VCA
    vca_out = math.min(1.0, math.max(-1.0, mix_out * vca_gain))
end

--------------------------------------------------------------------------------
-- KNOBS
--------------------------------------------------------------------------------

vco2_detune = 0.5
vca_gain = 0.4

--------------------------------------------------------------------------------
-- MELODY
--------------------------------------------------------------------------------

next_kbd = coroutine.wrap(
    function()
        local D2 = 73.42 / cv_to_hz
        local A1 = 55.00 / cv_to_hz
        local F1 = 43.65 / cv_to_hz
        local D1 = 36.71 / cv_to_hz
        local samples_per_note = 0.2 * sr
        local melody = {
            D1, D1, D2, A1, D1, D1, F1, A1,
            D1, D1, D2, A1, D1, D2, A1, A1
        }
        while true do
            for i = 1, #melody do
                for j = 1, samples_per_note do
                    local gate = j < samples_per_note * 7 / 8 and 5.0 or 0.0
                    local cv = melody[i]
                    coroutine.yield(gate, cv)
                end
            end
        end
    end
)

--------------------------------------------------------------------------------
-- RUN
--------------------------------------------------------------------------------

while true do
    kbd_gate, kbd_cv = next_kbd()
    update()
    local sample = math.floor(128 + vca_out * 127)
    io.write(string.pack("<BB", sample, sample))
    io.flush()
end