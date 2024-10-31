#include <stdio.h>

#include <MiniFB.h>
#define PNTR_PIXELFORMAT_ARGB
#define PNTR_IMPLEMENTATION
#include "pntr.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define PNTR_SOUND_IMPLEMENTATION
#include "pntr_sound.h"

static pntr_image* screen;
static struct mfb_window* window;
static ma_engine* audio_engine;
static ma_sound* trap;

static ma_waveform* sineWave;

// this is a process-callback. engine also has a concept of a "data callback" that must be setup with intial config
void sound_process_example(void* pUserData, float* pFramesOut, ma_uint64 frameCount) {
  float sAud[frameCount];
  // grab current frame's worth of sinewave
  ma_waveform_read_pcm_frames(sineWave, sAud, frameCount, NULL);
  for (int i=0;i<frameCount;i++){
    // sine-wave ringmod
    pFramesOut[i] = (pFramesOut[i]/2.0) * sAud[i];
  }
}

void game_init() {
  // pntr_sound_global_volume(audio_engine, 0.5);
  trap = pntr_sound_load(audio_engine, "trap.mp3");
  if (trap != NULL) {
    pntr_sound_play(trap, true);
  } else {
    fprintf(stderr, "Cound not load trap.wav.\n");
  }
}

void game_update() {
  // demo gfx
  pntr_clear_background(screen, PNTR_RAYWHITE);
  pntr_draw_circle_fill(screen, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 80, PNTR_BLUE);
}

int main(int argc, char *argv[]) {
  window = mfb_open_ex("minipntr", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (!window) {
    fprintf(stderr, "Cound not open window.\n");
    return 1;
  }
  
  screen = pntr_new_image(SCREEN_WIDTH, SCREEN_HEIGHT);

  audio_engine = pntr_get_sound_engine();
  if (audio_engine == NULL) {
    fprintf(stderr, "Cound not open sound.\n");
    return 1;
  }

  // build a sinewave
  ma_waveform_config sineWaveConfig = ma_waveform_config_init(ma_format_f32, 2, 48000, ma_waveform_type_sine, 0.2, 440);
  ma_waveform_init(&sineWaveConfig, sineWave);


  // optional, this gets called on every process-tick, along with other sound stuff (playing samples, etc)
  pntr_sound_register_process(audio_engine, sound_process_example);

  game_init();
  
  while(mfb_update_ex(window, screen->data, SCREEN_WIDTH, SCREEN_HEIGHT) >= 0) {
    game_update();
    mfb_wait_sync(window);
  }

  pntr_unload_sound_engine(audio_engine);
  return 0;
}

