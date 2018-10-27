#include "editor.h"
#include "parser.h"
#include "audio.h"
#include <inttypes.h>


#include <math.h>

static char *device = "plughw:0,0";			/* playback device */
static snd_pcm_format_t format = SND_PCM_FORMAT_S8;	/* sample format */
static unsigned int rate = 44100;			/* stream rate */
static unsigned int channels = 1;			/* count of channels */
static unsigned int buffer_time = 500000;		/* ring buffer length in us */
static double freq = 440;				/* sinusoidal wave frequency in Hz */
static int verbose = 1;					/* verbose flag */
static int resample = 1;				/* enable alsa-lib resampling */
static snd_pcm_sframes_t buffer_size;
static snd_pcm_sframes_t period_size;

struct async_private_data data;
snd_pcm_t *handle;
snd_async_handler_t *ahandler;



void init(){
  enableRawMode();
  editorInitialize();

  if(parser_init()){
    printf("parser_init failed\n");
    exit(EXIT_FAILURE);
  }

}

void update_screen(){
  static clock_t last_update_tick = 0;

  clock_t current_tick = clock();
  if(current_tick-last_update_tick > 10000)
  {
    last_update_tick = current_tick;
    editorRefreshScreen();
  }
}

void evaluateCode() {
  int len;
  char *buf = editorRowsToString(&len);
  int err = parser_update(buf);
  if(err){
    printf("Err: %d CODE: %s",err,buf);
    exit(EXIT_FAILURE);
  }
  free(buf);
}

void read_input() {
  if (editorKeyboardHit())
  {
    int c = editorReadKey();
    switch (c) {
      case CTRL_KEY('e'):
      //case '\r':
        evaluateCode();
        break;
      default:
        editorProcessKey(c);
    }
  }
}



static void audio_fill(const snd_pcm_channel_area_t *areas,	int count)
{
	uint8_t *samples;
	samples = (uint8_t *) areas[0].addr;
	/* fill the channel areas */
	while (count-- > 0) {
		int res;
    res = parser_eval() * 127;
		*samples = res & 0xff;
		samples++; //advance sample
    parser_step(1); //advance step
	}
}


static void async_callback(snd_async_handler_t *ahandler)
{
	snd_pcm_t *handle = snd_async_handler_get_pcm(ahandler);
	struct async_private_data *data = snd_async_handler_get_callback_private(ahandler);
	signed short *samples = data->samples;
	snd_pcm_channel_area_t *areas = data->areas;
	snd_pcm_sframes_t avail;
	int err;

	avail = snd_pcm_avail_update(handle);
	while (avail >= period_size) {
		audio_fill(areas, period_size);
		err = snd_pcm_writei(handle, samples, period_size);
		if (err < 0) {
			printf("Write error: %s\n", snd_strerror(err));
			exit(EXIT_FAILURE);
		}
		if (err != period_size) {
			printf("Write error: written %i expected %li\n", err, period_size);
			exit(EXIT_FAILURE);
		}
		avail = snd_pcm_avail_update(handle);
	}
}


void async_kickoff(snd_pcm_t *handle,
		      signed short *samples,
		      snd_pcm_channel_area_t *areas)
{
	int err, count;
	data.samples = samples;
	data.areas = areas;
	err = snd_async_add_pcm_handler(&ahandler, handle, async_callback, &data);
	if (err < 0) {
		printf("Unable to register async handler\n");
		exit(EXIT_FAILURE);
	}
	for (count = 0; count < 2; count++) {
		audio_fill(areas, period_size);
		err = snd_pcm_writei(handle, samples, period_size);
		if (err < 0) {
			printf("Initial write error: %s\n", snd_strerror(err));
			exit(EXIT_FAILURE);
		}
		if (err != period_size) {
			printf("Initial write error: written %i expected %li\n", err, period_size);
			exit(EXIT_FAILURE);
		}
	}
	if (snd_pcm_state(handle) == SND_PCM_STATE_PREPARED) {
		err = snd_pcm_start(handle);
		if (err < 0) {
			printf("Start error: %s\n", snd_strerror(err));
			exit(EXIT_FAILURE);
		}
	}
}




int main()
{
	int err;
	snd_pcm_hw_params_t *hwparams;
	snd_pcm_sw_params_t *swparams;
	uint8_t *samples;
	snd_pcm_channel_area_t *areas;
	snd_pcm_hw_params_alloca(&hwparams);
	snd_pcm_sw_params_alloca(&swparams);

	if ((err = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
		printf("Playback open error: %s\n", snd_strerror(err));
		return 0;
	}
	if ((err = set_hwparams(handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED, &buffer_size, &period_size)) < 0) {
		printf("Setting of hwparams failed: %s\n", snd_strerror(err));
		exit(EXIT_FAILURE);
	}
	if ((err = set_swparams(handle, swparams,buffer_size,  period_size)) < 0) {
		printf("Setting of swparams failed: %s\n", snd_strerror(err));
		exit(EXIT_FAILURE);
	}

	samples = malloc((period_size * snd_pcm_format_physical_width(format)) / 8);
	if (samples == NULL) {
		printf("No enough memory\n");
		exit(EXIT_FAILURE);
	}

	areas = calloc(1, sizeof(snd_pcm_channel_area_t));
	if (areas == NULL) {
		printf("No enough memory\n");
		exit(EXIT_FAILURE);
	}

	areas[0].addr = samples;
	areas[0].first = 0;
	areas[0].step = 1;

	async_kickoff(handle, samples, areas);

  init();

  while (1) {
    read_input();
    update_screen();
  }


	free(areas);
	free(samples);
	snd_pcm_close(handle);
  // to satisfy compiler
  return 0;
}
