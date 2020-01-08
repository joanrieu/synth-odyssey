--------------------------------------------------------------------------------
-- NOISE GENERATOR
--------------------------------------------------------------------------------

-- knobs
noise_white = true

-- internal
-- Trammel Stochastic Algorithm
-- https://web.archive.org/web/20160705171002/http://home.earthlink.net/~ltrammell/tech/pinkalg.htm
local function noise_pink_band(amplitude, probability)
    return coroutine.wrap(
        function()
            while true do
                local sample = amplitude * math.random(-1, 1)
                repeat
                    local random = coroutine.yield(sample)
                until random > probability
            end
        end
    )
end
noise_pink_amp = 4.6306e-3 + 5.9961e-3 + 8.3586e-3
noise_pink_band_1 = noise_pink_band(4.6306e-3 / noise_pink_amp, 3.1878e-1)
noise_pink_band_2 = noise_pink_band(5.9961e-3 / noise_pink_amp, 7.7686e-1)
noise_pink_band_3 = noise_pink_band(8.3586e-3 / noise_pink_amp, 9.7785e-1)

-- out
noise_out = 0

function update_noise()
    if noise_white then
        noise_out = math.random(-1, 1)
    else
        local random = math.random()
        noise_out = noise_pink_band_1(random) + noise_pink_band_2(random) + noise_pink_band_3(random)
    end
end
