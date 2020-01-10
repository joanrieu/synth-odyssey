--------------------------------------------------------------------------------
-- LOW-FREQUENCY OSCILLATOR
--------------------------------------------------------------------------------

-- knobs
lfo_freq = 0

-- internal
lfo_step = 0

-- out
lfo_sine = 0
lfo_square = 0
lfo_trigger = false

function update_lfo()
    lfo_step = lfo_step + 1
    local steps = lfo_freq > 0 and sr / lfo_freq or 0
    if lfo_step < steps then
        lfo_sine = math.sin(2 * math.pi * lfo_step / steps)
        lfo_square = lfo_sine > 0 and 1 or -1
        lfo_trigger = false
    else
        lfo_step = 0
        lfo_sine = 0
        lfo_square = 0
        lfo_trigger = true
    end
end
