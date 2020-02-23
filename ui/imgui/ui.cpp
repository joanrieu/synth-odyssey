#include <GLFW/glfw3.h>
#include <imgui.h>

#include "../../core/synth.hpp"

#define KEY(name) GLFW_KEY_##name

struct Note {
    const char* name;
    float frequency;
    int key;
};

const Note notes[] = {
    { "C3", 130.8128, GLFW_KEY_A },
    { "D3", 146.8324, GLFW_KEY_S },
    { "E3", 164.8138, GLFW_KEY_D },
    { "F3", 174.6141, GLFW_KEY_F },
    { "G3", 195.9977, GLFW_KEY_G },
    { "A3", 220.0000, GLFW_KEY_H },
    { "B3", 246.9417, GLFW_KEY_J },
    { "C4", 261.6256, GLFW_KEY_K },
    { "D4", 293.6648, GLFW_KEY_L },
};

void style() {
    auto& style = ImGui::GetStyle();
    style.WindowRounding = 2;
    style.WindowTitleAlign = ImVec2(.5, .5);
    style.Colors[ImGuiCol_TitleBg] =
    style.Colors[ImGuiCol_TitleBgActive] =
        ImColor(0, 0, 0, 0);
}

void style_key(bool active) {
    auto white = ImColor(255, 255, 255, 255).Value;
    auto grey = ImColor(200, 200, 200, 255).Value;
    auto color = active ? grey : white;
    ImGui::PushStyleColor(ImGuiCol_Button, color);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, grey);
}

void unstyle_key() {
    ImGui::PopStyleColor(2);
}

void decoration() {
    const auto fg = ImGui::GetForegroundDrawList();
    const auto p_min = ImVec2(0, 0);
    const auto p_max = ImGui::GetIO().DisplaySize;
    fg->AddRectFilledMultiColor(
        p_min,
        p_max,
        ImColor(255, 255, 255, 25),
        ImColor(255, 255, 255, 50),
        ImColor(255, 255, 255, 25),
        ImColor(255, 255, 255, 50)
    );
}

void slider(const char* name, float* value, const float min, const float max, const float power = 1.0f) {
    ImGui::SliderScalar(name, ImGuiDataType_Float, value, &min, &max, NULL, power);
}

void toggle(const char* name, bool* value) {
    ImGui::Checkbox(name, value);
}

void toggle(const char* name_on, const char* name_off, bool* value) {
    int on = *value;
    ImGui::RadioButton(name_on, &on, 1);
    ImGui::SameLine();
    ImGui::RadioButton(name_off, &on, 0);
    *value = on;
}

void slider_toggle(
    const char* name,
    const char* name_on,
    const char* name_off,
    bool* bool_value,
    float* float_value,
    const float min,
    const float max,
    const float power = 1.0f
) {
    ImGui::PushID(float_value);
    slider(name, float_value, min, max, power);
    ImGui::SameLine();
    toggle(name_on, name_off, bool_value);
    ImGui::PopID();
}

void keyboard(Synth& synth) {
    float freq = synth.kbd.freq_target;
    bool trigger = false, gate = false;

    ImGui::NewLine();
    for (const auto& note : notes) {
        if (ImGui::GetCursorPosY() > 0) {
            ImGui::SameLine(0, 0);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 1);
        }
        style_key(synth.kbd.gate && synth.kbd.freq_target == note.frequency);
        ImGui::Button(note.name, ImVec2(60, 130));
        unstyle_key();

        if (
            ImGui::IsKeyPressed(note.key, false) ||
            ImGui::IsItemActivated()
        ) {
            trigger = true;
        }

        if (
            ImGui::IsKeyDown(note.key) ||
            ImGui::IsItemActive()
        ) {
            freq = note.frequency;
            gate = true;
        }
    }

    synth.kbd.freq_target = freq;
    synth.kbd.trigger = trigger;
    synth.kbd.gate = gate;
}

void patch(Synth& synth) {
    if (ImGui::Button("Load")) {
        synth.kbd.portamento = 0.5;
        synth.kbd.transpose = -2;
        synth.ar.release = 0.1;
        synth.adsr.decay = 0.1;
        synth.adsr.sustain = 0.2;
        synth.vco1.tune = 1;
        synth.vco2.tune = 1;
        synth.vco2.detune = 3.14;
        synth.lfo.freq = 3.14;
        synth.mix.vco1 = 1;
        synth.mix.vco2 = 1;
        synth.vcf.cutoff = 5000;
        synth.vcf.reso = 0.2;
        synth.vcf.mod2 = 0.1;
        synth.vcf.mod2_sh = false;
        synth.vcf.env = 0.9;
        synth.vca.env = 5;
    }
}

void render(Synth& synth) {
    static const auto window_flags =
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_AlwaysAutoResize;

    style();
    decoration();

    ImGui::Begin("VCO 1", NULL, window_flags);
    slider("Tune (coarse)", &synth.vco1.tune, 0, 16, 2);
    slider("Tune (fine)", &synth.vco1.detune, 0, 16, 2);
    toggle("Audio (keyboard on)", "LF (keyboard off)", &synth.vco1.kbd);
    slider_toggle("FM 1", "LFO Sine", "LFO Square", &synth.vco1.fm1_is_lfo_sine, &synth.vco1.fm1, 0, 1);
    slider_toggle("FM 2", "SH", "ADSR", &synth.vco1.fm2_is_sh_out, &synth.vco1.fm2, 0, 1);
    slider("PW", &synth.vco1.pw, 0, 1);
    slider_toggle("PWM", "LFO Sine", "ADSR", &synth.vco1.pwm_is_lfo, &synth.vco1.pwm, 0, 1);
    ImGui::End();

    ImGui::Begin("VCO 2", NULL, window_flags);
    slider("Tune (coarse)", &synth.vco2.tune, 0, 16, 2);
    slider("Tune (fine)", &synth.vco2.detune, 0, 16, 2);
    toggle("Sync", &synth.vco2.sync);
    slider_toggle("FM 1", "LFO Sine", "SH Mix", &synth.vco2.fm1_is_lfo_sine, &synth.vco2.fm1, 0, 1);
    slider_toggle("FM 2", "SH", "ADSR", &synth.vco2.fm2_is_sh_out, &synth.vco2.fm2, 0, 1);
    slider("PW", &synth.vco2.pw, 0, 1);
    slider_toggle("PWM", "LFO Sine", "ADSR", &synth.vco2.pwm_is_lfo, &synth.vco2.pwm, 0, 1);
    ImGui::End();

    ImGui::Begin("VCF", NULL, window_flags);
    slider("Cutoff", &synth.vcf.cutoff, 0, 16000, 2);
    slider("Resonance", &synth.vcf.reso, 0, 100, 2);
    slider_toggle("FM 1", "Keyboard", "SH Mix", &synth.vcf.mod1_kbd, &synth.vcf.mod1, 0, 1);
    slider_toggle("FM 2", "SH", "LFO Sine", &synth.vcf.mod2_sh, &synth.vcf.mod2, 0, 1);
    slider_toggle("Envelope", "ADSR", "AR", &synth.vcf.env_adsr, &synth.vcf.env, 0, 1);
    ImGui::End();

    ImGui::Begin("LFO", NULL, window_flags);
    slider("Frequency", &synth.lfo.freq, 0, 20, 2);
    ImGui::End();

    ImGui::Begin("SAMPLE / HOLD", NULL, window_flags);
    slider_toggle("VCO 1", "Saw", "Square", &synth.sh.vco1_saw, &synth.sh.vco1, 0, 1);
    slider_toggle("", "Noise", "VCO 2", &synth.sh.noise_gen, &synth.sh.noise, 0, 1);
    toggle("LFO Trigger", "Keyboard Trigger", &synth.sh.lfo_trigger);
    slider("Output Lag", &synth.sh.lag, 0, 1);
    ImGui::End();

    ImGui::Begin("NOISE", NULL, window_flags);
    toggle("White", "Pink", &synth.noise.white);
    ImGui::End();

    ImGui::Begin("MIXER", NULL, window_flags);
    slider_toggle("VCO 1", "Saw", "Square", &synth.mix.vco1_saw, &synth.mix.vco1, 0, 1);
    slider_toggle("VCO 2", "Saw", "Square", &synth.mix.vco2_saw, &synth.mix.vco2, 0, 1);
    slider_toggle("", "Noise", "Ring", &synth.mix.noise, &synth.mix.noise_ring, 0, 1);
    ImGui::End();

    ImGui::Begin("HPF", NULL, window_flags);
    slider("Cutoff", &synth.hpf.cutoff, 0, 16000, 2);
    ImGui::End();

    ImGui::Begin("AR", NULL, window_flags);
    slider("Attack", &synth.ar.attack, 0, 1);
    slider("Release", &synth.ar.release, 0, 1);
    toggle("Keyboard Trigger", &synth.ar.kbd_trigger);
    ImGui::End();

    ImGui::Begin("ADSR", NULL, window_flags);
    slider("Attack", &synth.adsr.attack, 0, 1);
    slider("Sustain", &synth.adsr.sustain, 0, 1);
    slider("Decay", &synth.adsr.decay, 0, 1);
    slider("Release", &synth.adsr.release, 0, 1);
    toggle("Keyboard Gate", "LFO Repeat", &synth.adsr.kbd_trigger);
    toggle("Keyboard Repeat", "Auto Repeat", &synth.adsr.kbd_repeat);
    ImGui::End();

    ImGui::Begin("VCA", NULL, window_flags);
    slider_toggle("Envelope", "AR", "ADSR", &synth.vca.env_ar, &synth.vca.env, 0, 1);
    slider("Gain", &synth.vca.gain, 0, 1);
    ImGui::End();

    ImGui::Begin("KEYBOARD CONTROL", NULL, window_flags);
    slider("Portamento", &synth.kbd.portamento, 0, 1);
    slider("Transpose", &synth.kbd.transpose, -2, 2);
    toggle("Sequencer", &synth.kbd.sequencer);
    ImGui::End();

    ImGui::Begin("KEYBOARD", NULL, window_flags);
    keyboard(synth);
    ImGui::End();

    ImGui::Begin("PATCH", NULL, window_flags);
    patch(synth);
    ImGui::End();
}
