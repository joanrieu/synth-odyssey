--------------------------------------------------------------------------------
-- VOLTAGE-CONTROLLED FILTER
--------------------------------------------------------------------------------

-- knobs
vcf_cutoff = 1/0
vcf_reso = 0
vcf_env = 0
vcf_env_adsr = true

-- internal
vcf_2vt = 2 * 0.025 -- Vt = 25mV
vcf_a = 0
vcf_a_tanh = 0
vcf_b = 0
vcf_b_tanh = 0
vcf_c = 0
vcf_c_tanh = 0
vcf_d = 0
vcf_d_tanh = 0

-- out
vcf_out = 0

function update_vcf()
    local env = vcf_env * (vcf_env_adsr and adsr_out or ar_out)
    local cutoff = (env + (1 - vcf_env)) * vcf_cutoff

    -- Non-Linear Digital Implementation of the Moog Ladder Filter
    -- https://web.archive.org/web/20060501012842/http://dafx04.na.infn.it/WebProc/Proc/P_061.pdf
    local g = 1 - math.exp(-2 * math.pi * cutoff / sr)
    local x = mix_out - 4 * vcf_reso * vcf_out
    vcf_a_tanh = math.tanh(vcf_a / vcf_2vt)
    vcf_a = vcf_a + vcf_2vt * g * (math.tanh(x / vcf_2vt) - vcf_a_tanh)
    vcf_b_tanh = math.tanh(vcf_b / vcf_2vt)
    vcf_b = vcf_b + vcf_2vt * g * (vcf_a_tanh - vcf_b_tanh)
    vcf_c_tanh = math.tanh(vcf_c / vcf_2vt)
    vcf_c = vcf_c + vcf_2vt * g * (vcf_b_tanh - vcf_c_tanh)
    vcf_d_tanh = math.tanh(vcf_out / vcf_2vt)
    vcf_d = vcf_out + vcf_2vt * g * (vcf_c_tanh - vcf_d_tanh)
    
    vcf_out = vcf_d
end
