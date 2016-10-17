#ifndef __AUDIO_AUDIO_H
#define __AUDIO_AUDIO_H

#include <inttypes.h>

void audio_open();
void audio_close();
void audio_update(struct movingobject *moving_objects, uint16_t player_engine_pitch, uint16_t player_engine_sound_active, uint16_t skidding_volume);
void audio_play_effect(int effect_index);

#endif

