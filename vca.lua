--------------------------------------------------------------------------------
-- VOLTAGE-CONTROLLED AMPLIFIER
--------------------------------------------------------------------------------

-- knobs
vca_env = 0
vca_env_ar = true
vca_gain = 0

-- out
vca_out = 0

function update_vca()
    local env = vca_env_ar and ar_out or adsr_out
    vca_out = (vca_env * env + vca_gain) * hpf_out
end
