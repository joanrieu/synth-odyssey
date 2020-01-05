--------------------------------------------------------------------------------
-- GLOBAL
--------------------------------------------------------------------------------

sr = 44100
cv_to_hz = 440.0 / 8.0

function run()
    vco2_detune = 2.0
    vcf_cutoff = 60.0
    vcf_reso = 4.0
    vca_gain = 2.0

    while true do
        update()
        local sample = math.floor(128 + vca_out * 127)
        io.write(string.pack("<BB", sample, sample))
        io.flush()
    end
end

function update()
    update_kbd()
    update_vco1()
    update_vco2()
    update_mix()
    update_vcf()
    update_hpf()
    update_vca()
end

--------------------------------------------------------------------------------
-- KEYBOARD / SEQUENCER
--------------------------------------------------------------------------------

-- out
kbd_gate = 0.0
kbd_cv = 0.0

update_kbd = coroutine.wrap(
    function()
        local D2 = 73.42 / cv_to_hz
        local A1 = 55.00 / cv_to_hz
        local F1 = 43.65 / cv_to_hz
        local D1 = 36.71 / cv_to_hz
        local samples_per_note = 0.2 * sr
        local melody = {
            D1, D1, D2, A1, D1, D1, F1, A1,
            D1, D1, D2, A1, D1, D2, A1, A1
        }
        while true do
            for i = 1, #melody do
                for j = 1, samples_per_note do
                    kbd_gate = j < samples_per_note * 7 / 8 and 5.0 or 0.0
                    kbd_cv = melody[i]
                    coroutine.yield()
                end
            end
        end
    end
)

--------------------------------------------------------------------------------
-- VCO 1
--------------------------------------------------------------------------------

-- knobs
vco1_tune = 1.0
vco1_detune = 0.0

-- out
vco1_saw = 0.0
vco1_square = 0.0

function update_vco1()
    if kbd_gate > 1 then
        local step = 2 * kbd_cv * cv_to_hz * (vco1_tune + vco1_detune / 100) / sr
        vco1_saw = vco1_saw + step
        if vco1_saw >= 1 then
            vco1_saw = -1
        end
        if vco1_saw > 0 then
            vco1_square = 1
        else
            vco1_square = -1
        end
    else
        vco1_saw = 0
    end
end

--------------------------------------------------------------------------------
-- VCO 2
--------------------------------------------------------------------------------

-- knobs
vco2_tune = 1.0
vco2_detune = 0.0

-- out
vco2_saw = 0.0
vco2_square = 0.0

function update_vco2()
    if kbd_gate > 1 then
        local step = 2 * kbd_cv * cv_to_hz * (vco2_tune + vco2_detune / 100) / sr
        vco2_saw = vco2_saw + step
        if vco2_saw >= 1 then
            vco2_saw = -1
        end
        if vco2_saw > 0 then
            vco2_square = 1
        else
            vco2_square = -1
        end
    else
        vco2_saw = 0
    end
end

--------------------------------------------------------------------------------
-- MIXER
--------------------------------------------------------------------------------

-- out
mix_out = 0.0

function update_mix()
    mix_out = vco1_saw * .7 + vco2_square * .3
end

--------------------------------------------------------------------------------
-- VCF
--------------------------------------------------------------------------------

-- knobs
vcf_cutoff = 0.0
vcf_reso = 0.0

-- internal
vcf_2vt = 2.0 * 0.025 -- Vt = 25mV
vcf_a = 0.0
vcf_a_tanh = 0.0
vcf_b = 0.0
vcf_b_tanh = 0.0
vcf_c = 0.0
vcf_c_tanh = 0.0
vcf_d = 0.0
vcf_d_tanh = 0.0

-- out
vcf_out = 0.0

-- https://web.archive.org/web/20060501012842/http://dafx04.na.infn.it/WebProc/Proc/P_061.pdf
function update_vcf()
    local cutoff = vcf_cutoff * cv_to_hz
    local g = 1.0 - math.exp(-2.0 * math.pi * cutoff / sr)
    local r = vcf_reso / 5.0
    local x = mix_out - 4.0 * r * vcf_out
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

--------------------------------------------------------------------------------
-- HPF
--------------------------------------------------------------------------------

-- knobs
hpf_cutoff = 0.0

-- internal
hpf_low = 0.0

-- out
hpf_out = 0.0

-- TODO: replace by a better filter
function update_hpf()
    local b = hpf_cutoff / 5.0
    local a = 1.0 - b
    hpf_low = a * hpf_low + b * vcf_out
    hpf_out = vcf_out - hpf_low
end

--------------------------------------------------------------------------------
-- VCA
--------------------------------------------------------------------------------

-- knobs
vca_gain = 0.0

-- out
vca_out = 0.0

function update_vca()
    vca_out = math.min(1.0, math.max(-1.0, hpf_out * vca_gain))
end

--------------------------------------------------------------------------------

run()
