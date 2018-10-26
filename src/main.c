#include "tinyexpr.h"
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

static char *device = "default";                        /* playback device */
uint8_t buffer[2];                          /* some random data */
snd_pcm_t *handle;

char expr[100];
uint8_t expr_index=0;


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


void loop(){

    int c = '\0';

     double t,r,f,v;
     r = 8000.0;
     f = 261.6;
     v = 127.0;
     te_variable vars[] = {{"t", &t},{"r", &r},{"f", &f},{"v", &v}};


     int err;
     //te_expr *expr = te_compile("(t*5&t>>7)|(t*3&t>>10)", vars, 4, &err);
     te_expr *expre = te_compile("(sin(t*2*3.14/100)+1)*100", vars, 4, &err);

     uint8_t sample;
     for (t = 0; ; t++) {
       sample = (uint8_t)te_eval(expre);
       snd_pcm_writei(handle, &sample, 1);

        if (kbhit())
        {
          c = getchar();
          expr[expr_index] = c;
          expr_index++;
          expr[expr_index] = 0;
            printf("\n%s\n", expr);
            if(c=='\n') {
              expre = te_compile(&expr, vars, 4, &err);
            }
        }

     }

}


int main(void)
{
        int err;
        unsigned int i;
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

        loop();

        snd_pcm_close(handle);
        return 0;
}


/*


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
