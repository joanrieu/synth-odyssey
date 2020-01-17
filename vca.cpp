////////////////////////////////////////////////////////////////////////////////
// VOLTAGE-CONTROLLED AMPLIFIER
////////////////////////////////////////////////////////////////////////////////

// in
extern float
ar_out,
adsr_out,
hpf_out;

// knobs
float
vca_env = 0,
vca_gain = 0;
bool
vca_env_ar = true;

// out
float
vca_out = 0;

void update_vca() {
    auto env = vca_env_ar ? ar_out : adsr_out;
    vca_out = (vca_env * env + vca_gain) * hpf_out;
}
