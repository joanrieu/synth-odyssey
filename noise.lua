--------------------------------------------------------------------------------
-- NOISE GENERATOR
--------------------------------------------------------------------------------

-- knobs
noise_white = true

function update_noise()
    if noise_white then
        noise_out = math.random()
    else
        -- TODO: pink noise
    end
end
