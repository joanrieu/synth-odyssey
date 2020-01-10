--------------------------------------------------------------------------------
-- SAMPLE / HOLD
--------------------------------------------------------------------------------

-- knobs
sh_vco1 = 0
sh_vco1_saw = true
sh_noise = 0
sh_noise_gen = true
sh_lfo_trigger = true

-- out
sh_mix = 0
sh_out = 0

function update_sh()
    local vco1 = sh_vco1 * (sh_vco1_saw and vco1_saw or vco1_square)
    local noise_vco2 = sh_noise * (sh_noise_gen and noise_out or vco2_square)
    sh_mix = (vco1 + noise_vco2) / math.max(1, sh_vco1 + sh_noise)
    local trigger = sh_lfo_trigger and lfo_trigger or kbd_trigger
    if trigger then
        sh_out = sh_mix
    end
end
