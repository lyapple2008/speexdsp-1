#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "speex/speex_echo.h"
#include "speex/speex_preprocess.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "wav_io.h"


#define NN 128
#define TAIL 1024

int main(int argc, char **argv)
{
   FILE *echo_fd, *ref_fd, *e_fd;
   short echo_buf[NN], ref_buf[NN], e_buf[NN];
   SpeexEchoState *st;
   SpeexPreprocessState *den;
   int sampleRate = 8000;

   if (argc != 4)
   {
      fprintf(stderr, "testecho mic_signal.sw speaker_signal.sw output.sw\n");
      exit(1);
   }
   echo_fd = fopen(argv[2], "rb");
   ref_fd  = fopen(argv[1],  "rb");
   e_fd    = fopen(argv[3], "wb");

   // parse wav
   WAV_HEADER ref_header;
   WAV_HEADER echo_header;
   
   if (read_header(&ref_header, ref_fd) != 0 || read_header(&echo_header, echo_fd) != 0) {
      fprintf(stderr, "fail to parse wav header\n");
      exit(1);
   }

   if (ref_header.format.sample_per_sec != echo_header.format.sample_per_sec ||
       ref_header.format.channels != 1 ||
       echo_header.format.channels != 1) {
      fprintf(stderr, "not support wav format\n");
      exit(1);
   }

   write_header(&ref_header, e_fd);

   sampleRate = ref_header.format.sample_per_sec;

   st = speex_echo_state_init(NN, TAIL);
   den = speex_preprocess_state_init(NN, sampleRate);
   speex_echo_ctl(st, SPEEX_ECHO_SET_SAMPLING_RATE, &sampleRate);
   speex_preprocess_ctl(den, SPEEX_PREPROCESS_SET_ECHO_STATE, st);

   while (!feof(ref_fd) && !feof(echo_fd))
   {
      // fread(ref_buf, sizeof(short), NN, ref_fd);
      // fread(echo_buf, sizeof(short), NN, echo_fd);
      read_samples(ref_buf, NN, &ref_header, ref_fd);
      read_samples(echo_buf, NN, &echo_header, echo_fd);

      speex_echo_cancellation(st, ref_buf, echo_buf, e_buf);
      speex_preprocess_run(den, e_buf);

      // fwrite(e_buf, sizeof(short), NN, e_fd);
      write_samples(e_buf, NN, &ref_header, e_fd);
   }
   speex_echo_state_destroy(st);
   speex_preprocess_state_destroy(den);
   fclose(e_fd);
   fclose(echo_fd);
   fclose(ref_fd);
   return 0;
}
