#include <imgui.h>
#include <lua.hpp>

static lua_State* L;

void slider(const char* name, const float min, const float max, const float power = 1.0f) {
    lua_getglobal(L, name);
    float value = lua_tonumber(L, -1);
    lua_pop(L, 1);
    if (ImGui::SliderScalar(name, ImGuiDataType_Float, &value, &min, &max, NULL, power)) {
        lua_pushnumber(L, value);
        lua_setglobal(L, name);
    }
}

void toggle(const char* name) {
    lua_getglobal(L, name);
    bool value = lua_toboolean(L, -1);
    lua_pop(L, 1);
    if (ImGui::Selectable(name, &value)) {
        lua_pushboolean(L, value);
        lua_setglobal(L, name);
    }
}

void render() {
    if (!L) {
        L = luaL_newstate();
        luaL_openlibs(L);
        luaL_dofile(L, "synth.lua");
    }

    ImGui::Begin("VCO1");
    slider("vco1_tune", 0, 16, 2);
    slider("vco1_detune", 0, 16, 2);
    toggle("vco1_kbd");
    slider("vco1_fm1", 0, 1);
    toggle("vco1_fm1_is_lfo_sine");
    slider("vco1_fm2", 0, 1);
    toggle("vco1_fm2_is_sh_out");
    slider("vco1_pw", 0, 1);
    slider("vco1_pwm", 0, 1);
    toggle("vco1_pwm_is_lfo");
    ImGui::End();

    ImGui::Begin("VCO2");
    slider("vco2_tune", 0, 16, 2);
    slider("vco2_detune", 0, 16, 2);
    slider("vco2_sync", 0, 1);
    slider("vco2_fm1", 0, 1);
    toggle("vco2_fm1_is_lfo_sine");
    slider("vco2_fm2", 0, 1);
    toggle("vco2_fm2_is_sh_out");
    slider("vco2_pw", 0, 1);
    slider("vco2_pwm", 0, 1);
    toggle("vco2_pwm_is_lfo");
    ImGui::End();

    ImGui::Begin("VCF");
    slider("vcf_cutoff", 0, 16000, 2);
    slider("vcf_reso", 0, 100, 2);
    slider("vcf_mod1", 0, 1);
    toggle("vcf_mod1_kbd");
    slider("vcf_mod2", 0, 1);
    toggle("vcf_mod2_sh");
    slider("vcf_env", 0, 1);
    toggle("vcf_env_adsr");
    ImGui::End();
    
    ImGui::Begin("ADSR");
    slider("adsr_attack", 0, 1);
    slider("adsr_sustain", 0, 1);
    slider("adsr_decay", 0, 1);
    slider("adsr_release", 0, 1);
    toggle("adsr_kbd_trigger");
    toggle("adsr_kbd_repeat");
    ImGui::End();

    lua_getglobal(L, "update");
    lua_pushnumber(L, 4096);
    lua_call(L, 1, 0);
}
