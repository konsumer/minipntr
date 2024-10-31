#ifdef PNTR_SOUND_IMPLEMENTATION
#define MINIAUDIO_IMPLEMENTATION
#endif

#include <miniaudio.h>

// initialize the sound-engine
ma_engine* pntr_get_sound_engine();

// register a processing callback
void pntr_sound_register_process(ma_engine* engine, ma_engine_process_proc cb);

// load an audio file
ma_sound* pntr_sound_load(ma_engine* engine, char* filename);

// play a loaded audio file
void pntr_sound_play(ma_sound* sound, bool loop);

// call this, when finished, to cleanup
void pntr_unload_sound_engine(ma_engine* engine);

// set the engine volume
void pntr_sound_global_volume(ma_engine* engine, float volume);


#ifdef PNTR_SOUND_IMPLEMENTATION

ma_engine* pntr_get_sound_engine() {
  ma_result result;
  ma_engine* engine = malloc(sizeof(ma_engine));
  result = ma_engine_init(NULL, engine);
  if (result != MA_SUCCESS) {
    return NULL;
  }
  return engine;
}

void pntr_sound_register_process(ma_engine* engine, ma_engine_process_proc cb) {
  engine->onProcess = cb;
}

ma_sound* pntr_sound_load(ma_engine* engine, char* filename) {
  ma_sound* sound = malloc(sizeof(ma_sound));
  ma_result result = ma_sound_init_from_file(engine, filename, 0, NULL, NULL, sound);
  if (result != MA_SUCCESS) {
      return NULL;
  }
  return sound;
}

void pntr_sound_play(ma_sound* sound, bool loop) {
  ma_sound_set_looping(sound, loop);
  ma_sound_start(sound);
}

void pntr_unload_sound_engine(ma_engine* engine) {
  ma_engine_uninit(engine);
  free(engine);
}

void pntr_sound_global_volume(ma_engine* engine, float volume) {
  ma_engine_set_volume(engine, volume);
}

#endif // PNTR_SOUND_IMPLEMENTATION
