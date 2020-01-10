require("kbd")
require("ar")
require("adsr")
require("vco1")
require("vco2")
require("lfo")
require("noise")
require("sh")
require("mix")
require("vcf")
require("hpf")
require("vca")
require("pcm")

oversampling = 2
sr = 44100 * oversampling

kbd_portamento = 0.5
ar_release = 0.1
adsr_decay = 0.1
adsr_sustain = 0.2
vco1_tune = 1
vco2_tune = 1
vco2_detune = math.pi
lfo_freq = math.pi
mix_vco1 = 1
mix_vco2 = 1
vcf_cutoff = 5000
vcf_reso = 0.2
vcf_mod2 = 0.1
vcf_mod2_sh = false
vcf_env = 0.9
vca_env = 5

function update()
    update_kbd()
    update_ar()
    update_adsr()
    update_vco1()
    update_vco2()
    update_lfo()
    update_noise()
    update_sh()
    update_mix()
    update_vcf()
    update_hpf()
    update_vca()
    update_pcm()
end

while true do
    update()
end
