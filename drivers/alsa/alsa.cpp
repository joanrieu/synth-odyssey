#include <cmath>
#include <pthread.h>
#include <alsa/asoundlib.h>

#include "../../lib/synth.hpp"

#define CHECK(pcm_op) if (pcm_op < 0) { abort(); }

void* driver_thread(void* data) {
    Synth& synth(*(Synth*)data);
	snd_pcm_t *pcm;
    snd_pcm_hw_params_t *params;
    CHECK(snd_pcm_open(&pcm, "default", SND_PCM_STREAM_PLAYBACK, 0));
    snd_pcm_hw_params_alloca(&params);
    CHECK(snd_pcm_hw_params_any(pcm, params));
    CHECK(snd_pcm_hw_params_set_access(pcm, params, SND_PCM_ACCESS_RW_INTERLEAVED));
    CHECK(snd_pcm_hw_params_set_format(pcm, params, SND_PCM_FORMAT_S32));
    CHECK(snd_pcm_hw_params_set_channels(pcm, params, 1));
    CHECK(snd_pcm_hw_params_set_rate_near(pcm, params, &synth.sr, 0));
    unsigned delay_us = 10000;
    CHECK(snd_pcm_hw_params_set_buffer_time_near(pcm, params, &delay_us, 0));
    CHECK(snd_pcm_hw_params(pcm, params));

	snd_pcm_uframes_t frames;
    CHECK(snd_pcm_hw_params_get_buffer_size(params, &frames));
    int32_t buffer[frames];
    for (;;) {
        for (snd_pcm_uframes_t i = 0; i < frames; ++i) {
            synth.update();
            buffer[i] = synth.vca.out * (1 << 31);
        }
        CHECK(snd_pcm_writei(pcm, buffer, frames));
    }
}

void driver(Synth& synth) {
    pthread_t thread;
    pthread_create(&thread, NULL, driver_thread, &synth);
}
