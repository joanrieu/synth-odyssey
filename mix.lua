--------------------------------------------------------------------------------
-- MIXER
--------------------------------------------------------------------------------

-- knob
mix_vco1 = 0
mix_vco1_saw = true
mix_vco2 = 0
mix_vco2_saw = true
mix_noise_ring = 0
mix_noise = true

-- out
mix_out = 0

function update_mix()
    local vco1 = mix_vco1_saw and vco1_saw or vco1_square
    local vco2 = mix_vco2_saw and vco2_saw or vco2_square
    local noise_ring = mix_noise and noise_out or vco1 * vco2
    mix_out = mix_vco1 * vco1 + mix_vco2 * vco2 + mix_noise_ring * noise_ring
end
