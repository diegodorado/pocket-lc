#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

static char *device = "default";                        /* playback device */
snd_output_t *output = NULL;
unsigned char buffer[16*1024];                          /* some random data */
int main(void)
{
        int err;
        unsigned int i;
        snd_pcm_t *handle;
        snd_pcm_sframes_t frames;
        for (i = 0; i < sizeof(buffer); i++)
                buffer[i] = random() & 0xff;
        if ((err = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
                printf("Playback open error: %s\n", snd_strerror(err));
                exit(EXIT_FAILURE);
        }
        if ((err = snd_pcm_set_params(handle,
                                      SND_PCM_FORMAT_U8,
                                      SND_PCM_ACCESS_RW_INTERLEAVED,
                                      1,
                                      44100,
                                      1,
                                      500000)) < 0) {   /* 0.5sec */
                printf("Playback open error: %s\n", snd_strerror(err));
                exit(EXIT_FAILURE);
        }
        for (i = 0; i < 16; i++) {
                frames = snd_pcm_writei(handle, buffer, sizeof(buffer));
                if (frames < 0)
                        frames = snd_pcm_recover(handle, frames, 0);
                if (frames < 0) {
                        printf("snd_pcm_writei failed: %s\n", snd_strerror(frames));
                        break;
                }
                if (frames > 0 && frames < (long)sizeof(buffer))
                        printf("Short write (expected %li, wrote %li)\n", (long)sizeof(buffer), frames);
        }
        snd_pcm_close(handle);
        return 0;
}

/*
#include "soundio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct SoundIo *soundio;
struct SoundIoDevice *device;
struct SoundIoOutStream *outstream;


static const float PI = 3.1415926535f;
static float seconds_offset = 0.0f;


static void write_callback(struct SoundIoOutStream *outstream,
        int frame_count_min, int frame_count_max)
{
    const struct SoundIoChannelLayout *layout = &outstream->layout;
    float float_sample_rate = outstream->sample_rate;
    float seconds_per_frame = 1.0f / float_sample_rate;
    struct SoundIoChannelArea *areas;
    int frames_left = frame_count_max;
    int err;

    while (frames_left > 0) {
        int frame_count = frames_left;

        if ((err = soundio_outstream_begin_write(outstream, &areas, &frame_count))) {
            fprintf(stderr, "%s\n", soundio_strerror(err));
            exit(1);
        }

        if (!frame_count)
            break;

        float pitch = 440.0f;
        float radians_per_second = pitch * 2.0f * PI;
        for (int frame = 0; frame < frame_count; frame += 1) {
            float sample = sinf((seconds_offset + frame * seconds_per_frame) * radians_per_second);
            for (int channel = 0; channel < layout->channel_count; channel += 1) {
                float *ptr = (float*)(areas[channel].ptr + areas[channel].step * frame);
                *ptr = sample;
            }
        }
        seconds_offset = fmodf(seconds_offset +
            seconds_per_frame * frame_count, 1.0f);

        if ((err = soundio_outstream_end_write(outstream))) {
            fprintf(stderr, "%s\n", soundio_strerror(err));
            exit(1);
        }

        frames_left -= frame_count;
    }
}



int initialize() {
    int err;
    soundio = soundio_create();
    if (!soundio) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }

    if ((err = soundio_connect(soundio))) {
        fprintf(stderr, "error connecting: %s", soundio_strerror(err));
        return 1;
    }

    soundio_flush_events(soundio);

    int default_out_device_index = soundio_default_output_device_index(soundio);
    if (default_out_device_index < 0) {
        fprintf(stderr, "no output device found");
        return 1;
    }

    device = soundio_get_output_device(soundio, default_out_device_index);
    if (!device) {
        fprintf(stderr, "out of memory");
        return 1;
    }

    fprintf(stderr, "Output device: %s\n", device->name);

    outstream = soundio_outstream_create(device);
    outstream->format = SoundIoFormatFloat32NE;
    outstream->write_callback = write_callback;

    if ((err = soundio_outstream_open(outstream))) {
        fprintf(stderr, "unable to open device: %s", soundio_strerror(err));
        return 1;
    }

    if (outstream->layout_error)
        fprintf(stderr, "unable to set channel layout: %s\n", soundio_strerror(outstream->layout_error));

    if ((err = soundio_outstream_start(outstream))) {
        fprintf(stderr, "unable to start device: %s", soundio_strerror(err));
        return 1;
    }
    return 0;
}

void finalize() {
  soundio_outstream_destroy(outstream);
  soundio_device_unref(device);
  soundio_destroy(soundio);
}


int main(int argc, char **argv) {
    int err = initialize();
    if ((err > 0) {
        return 1;
    }

    for (;;)
        soundio_wait_events(soundio);

    finalize()
    return 0;
}

*/


/*
 #include "tinyexpr.h"
 #include <stdio.h>
 #include <math.h>
 #include <stdint.h>



 #include <stdbool.h>
 #include <string.h>
 #include <termio.h>
 #include <unistd.h>

 bool kbhit(void)
 {
     struct termios original;
     tcgetattr(STDIN_FILENO, &original);

     struct termios term;
     memcpy(&term, &original, sizeof(term));

     term.c_lflag &= ~ICANON;
     tcsetattr(STDIN_FILENO, TCSANOW, &term);

     int characters_buffered = 0;
     ioctl(STDIN_FILENO, FIONREAD, &characters_buffered);

     tcsetattr(STDIN_FILENO, TCSANOW, &original);

     bool pressed = (characters_buffered != 0);

     return pressed;
 }

 void echoOff(void)
 {
     struct termios term;
     tcgetattr(STDIN_FILENO, &term);

     term.c_lflag &= ~ECHO;
     tcsetattr(STDIN_FILENO, TCSANOW, &term);
 }

 void echoOn(void)
 {
     struct termios term;
     tcgetattr(STDIN_FILENO, &term);

     term.c_lflag |= ECHO;
     tcsetattr(STDIN_FILENO, TCSANOW, &term);
 }

 int main(void)
 {
   long i;
   //echoOff();

   int c = '\0';

     while (c != 'q')
     {
         if (kbhit())
         {
             c = getchar();

             //printf("got key \'%c\'\n", c);
             if(c=='\n') { printf("\nuser break\n"); return 1;  }
         }
     }

     //echoOn();

     return 0;
 }


int main2(int argc, char *argv[])
{
  long i;
  echoOff();

  int c = '\0';



   double t,r,f,v;
   r = 8000.0;
   f = 261.6;
   v = 127.0;
   te_variable vars[] = {{"t", &t},{"r", &r},{"f", &f},{"v", &v}};


   int err;
   //te_expr *expr = te_compile("( sin(t) + 1 ) * v", vars, 4, &err);
   te_expr *expr = te_compile("(sin(t*2*3.14/r*f)+1)*v", vars, 4, &err);

  int d;
  int count = 0;
  char arr[12];


  d = getchar();

  while ((count < 12) && (d != EOF)) {
    arr[count] = d;
    ++count;
    d = getchar();
  }

  arr[count] = 0;
  printf("%s\n",&arr);



  return 1;



   if (expr) {
       for ( int i=0; ; i++ )
       {
         t = i;
         uint8_t temp = (uint8_t)te_eval(expr);
         //uint8_t temp = t/F*C; // middle C saw wave (bytebeat style)
         // uint8_t temp = (t*5&t>>7)|(t*3&t>>10); // viznut bytebeat composition
         fwrite(&temp,1,1,stdout);

         c += 0.002;


       }

       te_free(expr);
   } else {
       printf("Parse error at %d\n", err);
   }

   echoOn();

   return 0;



}
*/
