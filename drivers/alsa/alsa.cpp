#include <cmath>
#include <pthread.h>
#include <alsa/asoundlib.h>

#include "../../core/control.hpp"

#define CHECK(pcm_op) if (pcm_op < 0) { puts("ALSA driver error: " #pcm_op); exit(1); }

void* driver_thread(void* data) {
    SynthController& controller(*(SynthController*)data);
    const Synth& synth(controller.synth());
	snd_pcm_t *pcm;
    snd_pcm_hw_params_t *params;
    CHECK(snd_pcm_open(&pcm, "default", SND_PCM_STREAM_PLAYBACK, 0));
    snd_pcm_hw_params_alloca(&params);
    CHECK(snd_pcm_hw_params_any(pcm, params));
    CHECK(snd_pcm_hw_params_set_access(pcm, params, SND_PCM_ACCESS_RW_INTERLEAVED));
    CHECK(snd_pcm_hw_params_set_format(pcm, params, SND_PCM_FORMAT_S32));
    CHECK(snd_pcm_hw_params_set_channels(pcm, params, 1));
    unsigned sr = synth.sr;
    CHECK(snd_pcm_hw_params_set_rate_near(pcm, params, &sr, 0));
    controller.push_control({ ControlType::UNSIGNED, { UnsignedControl::SAMPLE_RATE, sr }});
    unsigned delay_us = 10000;
    CHECK(snd_pcm_hw_params_set_buffer_time_near(pcm, params, &delay_us, 0));
    CHECK(snd_pcm_hw_params(pcm, params));

	snd_pcm_uframes_t frames;
    CHECK(snd_pcm_hw_params_get_buffer_size(params, &frames));
    int32_t buffer[frames];
    for (;;) {
        for (snd_pcm_uframes_t i = 0; i < frames; ++i) {
            controller.update();
            buffer[i] = synth.vca.out * (1 << 31);
        }
        auto err = snd_pcm_writei(pcm, buffer, frames);
        if (err < 0) {
            err = snd_pcm_recover(pcm, err, 0);
            if (err < 0) exit(1);
        }
    }
}

void driver(SynthController& controller) {
    pthread_t thread;
    pthread_create(&thread, NULL, driver_thread, &controller);
}
