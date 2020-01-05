-- global
sr = 44100

-- KBD out
kbd_gate = 0.0
kbd_cv = 0.0

-- VCO 1 in
vco1_tune = 440.0 / 8.0 -- Hz/V

-- VCO 1 out
vco1_saw = 0.0
vco1_square = 0.0

-- VCA in
vca_gain = 0.0

-- VCA out
vca_out = 0.0

function update()
    -- VCO 1
    if kbd_gate > 1 then
        local step = 2 * kbd_cv * vco1_tune / sr
        vco1_saw = vco1_saw + step
        if vco1_saw >= 1 then
            vco1_saw = -1
        end
    else
        vco1_saw = 0
    end

    -- VCA
    vca_out = math.min(1.0, math.max(-1.0, vco1_saw * vca_gain))
end

kbd_gate = 5.0
kbd_cv = 8.0
vca_gain = 0.7

while true do
    update()
    local sample = math.floor(128 + vca_out * 127)
    io.write(string.pack("<BB", sample, sample))
    io.flush()
end