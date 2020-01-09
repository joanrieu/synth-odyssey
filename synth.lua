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

kbd_portamento = 0.5
ar_release = 0.1
adsr_decay = 0.1
adsr_sustain = 0.2
vco1_tune = 1
vco2_tune = 1
vco2_detune = math.pi
mix_vco1 = 1
mix_vco2 = 1
vcf_cutoff = 5000
vcf_reso = 0.2
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
    update_mix()
    update_vcf()
    update_hpf()
    update_vca()
end

function init_io()
    io.input():setvbuf("no")
    io.output():setvbuf("no")
end

function write_output()
    io.write(string.pack("<i4", math.min(2^31 - 1, math.max(-2^31, math.floor(vca_out * 2^31)))))
end

function run()
    init_io()
    while true do
        update()
        write_output()
    end
end

run()
