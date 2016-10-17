#ifndef __AUDIO_GORILLA_AUDIO_H
#define __AUDIO_GORILLA_AUDIO_H

#include <inttypes.h>

void gorilla_audio_open();
void gorilla_audio_start_engine_loop(int object_index);
void gorilla_audio_stop_engine_loop(int object_index);
void gorilla_audio_set_engine_attributes(int object_index, uint32_t pitch,uint16_t pan,int32_t volume);
void gorilla_audio_start_skidding_loop();
void gorilla_audio_stop_skidding_loop();
void gorilla_audio_set_skidding_loop_volume(int skidding_volume);
void gorilla_audio_update();
void gorilla_audio_close();

#endif

