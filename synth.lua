require("kbd")
require("ar")
require("adsr")
require("vco1")
require("vco2")
require("lfo")
require("noise")
require("mix")
require("vcf")
require("hpf")
require("vca")

sr = 44100

ar_attack = 0.01
ar_release = 1
adsr_decay = 0.5
vco1_tune = 2
vco1_lfo = .1
vco2_tune = 2
vco2_detune = 4
vco2_lfo = .1
lfo_freq = 10
mix_vco1 = 1
mix_vco2 = 1
mix_noise_ring = 1
vcf_cutoff = 4000
vcf_reso = 0.2
vcf_env = 0.85
vca_env = 4

function update()
    update_kbd()
    update_ar()
    update_adsr()
    update_vco1()
    update_vco2()
    update_lfo()
    update_noise()
    update_mix()
    update_vcf()
    update_hpf()
    update_vca()
end

function play()
    local clipped = (1 - 1e-6) * math.min(1, math.max(-1, vca_out))
    local sample = math.floor(clipped * 2^31)
    io.write(string.pack("<i4i4", sample, sample))
    io.flush()
end

while true do
    update()
    play()
end
