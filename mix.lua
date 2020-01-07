--------------------------------------------------------------------------------
-- MIXER
--------------------------------------------------------------------------------

-- knob
mix_vco1 = 0
mix_vco1_saw = true
mix_vco2 = 0
mix_vco2_saw = true

-- out
mix_out = 0

function update_mix()
    local vco1 = mix_vco1 * (mix_vco1_saw and vco1_saw or vco1_square)
    local vco2 = mix_vco2 * (mix_vco2_saw and vco2_saw or vco2_square)
    mix_out = vco1 + vco2
end
