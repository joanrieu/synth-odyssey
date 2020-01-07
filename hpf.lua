--------------------------------------------------------------------------------
-- HIGH-PASS FILTER
--------------------------------------------------------------------------------

-- knobs
hpf_cutoff = 0

-- internal
hpf_sample = 0

-- out
hpf_out = 0

function update_hpf()
    local rc = 1 / (2 * math.pi * hpf_cutoff)
    local inf = 1 / 0
    local a = rc < inf and rc / (rc + 1 / sr) or 1
    local delta = vcf_out - hpf_sample
    hpf_sample = vcf_out
    hpf_out = a * (hpf_out + delta)
end
