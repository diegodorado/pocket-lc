#include <stdint.h>
#include <alsa/asoundlib.h>

struct async_private_data {
	uint8_t *samples;
	snd_pcm_channel_area_t *areas;
};

int set_hwparams(snd_pcm_t *handle,snd_pcm_hw_params_t *params,snd_pcm_access_t access,snd_pcm_sframes_t *buffer_size,
snd_pcm_sframes_t *period_size);
int set_swparams(snd_pcm_t *handle, snd_pcm_sw_params_t *swparams, snd_pcm_sframes_t buffer_size, snd_pcm_sframes_t period_size);
