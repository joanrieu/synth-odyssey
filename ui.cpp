#include <cmath>
#include <GLFW/glfw3.h>
#include <imgui.h>

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

extern float
sr,
kbd_freq_target,
vco1_tune,
vco1_detune,
vco1_fm1,
vco1_fm2,
vco1_pw,
vco1_pwm,
vco2_tune,
vco2_detune,
vco2_fm1,
vco2_fm2,
vco2_pw,
vco2_pwm,
vcf_cutoff,
vcf_reso,
vcf_mod1,
vcf_mod2,
vcf_env,
lfo_freq,
sh_vco1,
sh_noise,
sh_lag,
mix_vco1,
mix_vco2,
mix_noise_ring,
hpf_cutoff,
ar_attack,
ar_release,
adsr_attack,
adsr_sustain,
adsr_decay,
adsr_release,
vca_env,
vca_gain,
kbd_portamento,
kbd_transpose;

extern bool
kbd_trigger,
kbd_gate,
vco1_kbd,
vco1_fm1_is_lfo_sine,
vco1_fm2_is_sh_out,
vco1_pwm_is_lfo,
vco2_sync,
vco2_fm1_is_lfo_sine,
vco2_fm2_is_sh_out,
vco2_pwm_is_lfo,
vcf_mod1_kbd,
vcf_mod2_sh,
vcf_env_adsr,
sh_vco1_saw,
sh_noise_gen,
sh_lfo_trigger,
noise_white,
mix_vco1_saw,
mix_vco2_saw,
mix_noise,
ar_kbd_trigger,
adsr_kbd_trigger,
adsr_kbd_repeat,
vca_env_ar,
kbd_sequencer;

extern void update();

void style() {
    auto& style = ImGui::GetStyle();
    style.WindowRounding = 2;
    style.WindowTitleAlign = ImVec2(.5, .5);
    style.Colors[ImGuiCol_TitleBg] =
    style.Colors[ImGuiCol_TitleBgActive] =
        ImColor(0, 0, 0, 0);
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

void keyboard() {
    kbd_trigger = false;
    kbd_gate = false;

    ImGui::NewLine();
    for (const auto& note : notes) {
        ImGui::SameLine(0, 0);
        ImGui::Button(note.name, ImVec2(130, 130));

        if (
            ImGui::IsKeyPressed(note.key, false) ||
            ImGui::IsItemActivated()
        ) {
            kbd_trigger = true;
        }

        if (
            ImGui::IsKeyDown(note.key) ||
            ImGui::IsItemActive()
        ) {
            kbd_gate = true;
            kbd_freq_target = note.frequency;
        }
    }
}

void render() {
    static bool is_init = false;
    if (!is_init) {
        is_init = true;
        kbd_portamento = 0.5;
        ar_release = 0.1;
        adsr_decay = 0.1;
        adsr_sustain = 0.2;
        vco1_tune = 1;
        vco2_tune = 1;
        vco2_detune = M_PI;
        lfo_freq = M_PI;
        mix_vco1 = 1;
        mix_vco2 = 1;
        vcf_cutoff = 5000;
        vcf_reso = 0.2;
        vcf_mod2 = 0.1;
        vcf_mod2_sh = false;
        vcf_env = 0.9;
        vca_env = 5;

        style();
    }

    static const auto window_flags =
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_AlwaysAutoResize;

    decoration();

    ImGui::Begin("VCO 1", NULL, window_flags);
    slider("vco1_tune", &vco1_tune, 0, 16, 2);
    slider("vco1_detune", &vco1_detune, 0, 16, 2);
    toggle("vco1_kbd", &vco1_kbd);
    slider("vco1_fm1", &vco1_fm1, 0, 1);
    toggle("vco1_fm1_is_lfo_sine", &vco1_fm1_is_lfo_sine);
    slider("vco1_fm2", &vco1_fm2, 0, 1);
    toggle("vco1_fm2_is_sh_out", &vco1_fm2_is_sh_out);
    slider("vco1_pw", &vco1_pw, 0, 1);
    slider("vco1_pwm", &vco1_pwm, 0, 1);
    toggle("vco1_pwm_is_lfo", &vco1_pwm_is_lfo);
    ImGui::End();

    ImGui::Begin("VCO 2", NULL, window_flags);
    slider("vco2_tune", &vco2_tune, 0, 16, 2);
    slider("vco2_detune", &vco2_detune, 0, 16, 2);
    toggle("vco2_sync", &vco2_sync);
    slider("vco2_fm1", &vco2_fm1, 0, 1);
    toggle("vco2_fm1_is_lfo_sine", &vco2_fm1_is_lfo_sine);
    slider("vco2_fm2", &vco2_fm2, 0, 1);
    toggle("vco2_fm2_is_sh_out", &vco2_fm2_is_sh_out);
    slider("vco2_pw", &vco2_pw, 0, 1);
    slider("vco2_pwm", &vco2_pwm, 0, 1);
    toggle("vco2_pwm_is_lfo", &vco2_pwm_is_lfo);
    ImGui::End();

    ImGui::Begin("VCF", NULL, window_flags);
    slider("vcf_cutoff", &vcf_cutoff, 0, 16000, 2);
    slider("vcf_reso", &vcf_reso, 0, 100, 2);
    slider("vcf_mod1", &vcf_mod1, 0, 1);
    toggle("vcf_mod1_kbd", &vcf_mod1_kbd);
    slider("vcf_mod2", &vcf_mod2, 0, 1);
    toggle("vcf_mod2_sh", &vcf_mod2_sh);
    slider("vcf_env", &vcf_env, 0, 1);
    toggle("vcf_env_adsr", &vcf_env_adsr);
    ImGui::End();

    ImGui::Begin("LFO", NULL, window_flags);
    slider("lfo_freq", &lfo_freq, 0, 20, 2);
    ImGui::End();

    ImGui::Begin("SAMPLE / HOLD", NULL, window_flags);
    slider("sh_vco1", &sh_vco1, 0, 1);
    toggle("sh_vco1_saw", &sh_vco1_saw);
    slider("sh_noise", &sh_noise, 0, 1);
    toggle("sh_noise_gen", &sh_noise_gen);
    toggle("sh_lfo_trigger", &sh_lfo_trigger);
    slider("sh_lag", &sh_lag, 0, 1);
    ImGui::End();

    ImGui::Begin("NOISE", NULL, window_flags);
    toggle("noise_white", &noise_white);
    ImGui::End();

    ImGui::Begin("MIXER", NULL, window_flags);
    slider("mix_vco1", &mix_vco1, 0, 1);
    toggle("mix_vco1_saw", &mix_vco1_saw);
    slider("mix_vco2", &mix_vco2, 0, 1);
    toggle("mix_vco2_saw", &mix_vco2_saw);
    slider("mix_noise_ring", &mix_noise_ring, 0, 1);
    toggle("mix_noise", &mix_noise);
    ImGui::End();

    ImGui::Begin("HPF", NULL, window_flags);
    slider("hpf_cutoff", &hpf_cutoff, 0, 16000, 2);
    ImGui::End();

    ImGui::Begin("AR", NULL, window_flags);
    slider("ar_attack", &ar_attack, 0, 1);
    slider("ar_release", &ar_release, 0, 1);
    toggle("ar_kbd_trigger", &ar_kbd_trigger);
    ImGui::End();

    ImGui::Begin("ADSR", NULL, window_flags);
    slider("adsr_attack", &adsr_attack, 0, 1);
    slider("adsr_sustain", &adsr_sustain, 0, 1);
    slider("adsr_decay", &adsr_decay, 0, 1);
    slider("adsr_release", &adsr_release, 0, 1);
    toggle("adsr_kbd_trigger", &adsr_kbd_trigger);
    toggle("adsr_kbd_repeat", &adsr_kbd_repeat);
    ImGui::End();

    ImGui::Begin("VCA", NULL, window_flags);
    slider("vca_env", &vca_env, 0, 1);
    toggle("vca_env_ar", &vca_env_ar);
    slider("vca_gain", &vca_gain, 0, 1);
    ImGui::End();

    ImGui::Begin("KEYBOARD", NULL, window_flags);
    slider("kbd_portamento", &kbd_portamento, 0, 1);
    ImGui::SameLine(0, ImGui::GetStyle().IndentSpacing);
    slider("kbd_transpose", &kbd_transpose, -2, 2);
    ImGui::SameLine(0, ImGui::GetStyle().IndentSpacing);
    toggle("kbd_sequencer", &kbd_sequencer);
    keyboard();
    ImGui::End();

    int samples = sr * ImGui::GetIO().DeltaTime;
    for (int i = 0; i < samples; ++i)
        update();
}
