void update_kbd();
void update_ar();
void update_adsr();
void update_vco1();
void update_vco2();
void update_lfo();
void update_noise();
void update_sh();
void update_mix();
void update_vcf();
void update_hpf();
void update_vca();
void update_pcm();

int
oversampling = 1;
float
sr = 44100 * oversampling;

void update() {
    update_kbd();
    update_ar();
    update_adsr();
    update_vco1();
    update_vco2();
    update_lfo();
    update_noise();
    update_sh();
    update_mix();
    update_vcf();
    update_hpf();
    update_vca();
    update_pcm();
}
