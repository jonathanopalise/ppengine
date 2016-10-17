#include "audio/audio.h"
#include "audio/gorilla/audio.h"
#include "stdio.h"
#include "engine.h"
#include <stdlib.h>

#define ENGINE_SOUND_COUNT 8

static int previous_car_object_type_and_visibility[ENGINE_SOUND_COUNT];
static int explosion_detection_enabled=0;
static int previous_player_engine_sound_active;
static int previous_player_type_and_visibility;
static int previous_skidding_volume;

void audio_open() {
	gorilla_audio_open();
}

void audio_close() {
	gorilla_audio_close();
}

void audio_update(struct movingobject *moving_objects, uint16_t player_engine_pitch, uint16_t player_engine_sound_active, uint16_t skidding_volume) {
	struct movingobject *current_object;
	int volume;
	int object_index;

	current_object=moving_objects;
	for (object_index=0; object_index<ENGINE_SOUND_COUNT-1; object_index++) {
		if (explosion_detection_enabled) {
			if ((current_object->type_and_visibility==0x8003) && (previous_car_object_type_and_visibility[object_index]!=0x8003)) {
				gorilla_audio_stop_engine_loop(object_index);
			} else if ((current_object->type_and_visibility==0x8002) && (previous_car_object_type_and_visibility[object_index]==0x2)) {
				gorilla_audio_start_engine_loop(object_index);
			} else if ((current_object->type_and_visibility==0x2) && (previous_car_object_type_and_visibility[object_index]==0x8002)) {
				gorilla_audio_stop_engine_loop(object_index);
			}
		}

		if (current_object->player_forward_position_difference>0) {
			volume=current_object->player_forward_position_difference/4;
		} else {
			volume=-current_object->player_forward_position_difference*2;
		}
		if (player_engine_sound_active) {
			if (volume>256) {
				volume=256;
			}
			volume=256-volume;
		} else {
			volume=0;
		}

		if (current_object->type_and_visibility==0x8002) {
			gorilla_audio_set_engine_attributes(
				object_index,
				current_object->current_speed,
				current_object->player_sideways_position_difference,
				volume
			);
		}
		previous_car_object_type_and_visibility[object_index]=current_object->type_and_visibility;
		current_object++;
	}

	current_object=&moving_objects[11];
	if ((current_object->type_and_visibility==0x8004) && (previous_player_type_and_visibility!=0x8004)) {
		//gorilla_audio_start_explosion(object_index);
	}
	if ((player_engine_sound_active&1)!=(previous_player_engine_sound_active&1)) {
		if (player_engine_sound_active) {
			gorilla_audio_start_engine_loop(ENGINE_SOUND_COUNT-1);
		} else {
			gorilla_audio_stop_engine_loop(ENGINE_SOUND_COUNT-1);
		}
	}
	if (player_engine_sound_active) {
		gorilla_audio_set_engine_attributes(
			ENGINE_SOUND_COUNT-1,
			player_engine_pitch*55000,
			0,
			256
		);
	}

	if (!player_engine_sound_active) {
		skidding_volume=0;
	}
	if (previous_skidding_volume!=skidding_volume) {
		if (skidding_volume==0) {
			gorilla_audio_stop_skidding_loop();
		} else {
			if (previous_skidding_volume==0) {
				gorilla_audio_start_skidding_loop();
			}
			gorilla_audio_set_skidding_loop_volume(skidding_volume);
		}
	}

	previous_player_engine_sound_active=player_engine_sound_active;
	previous_player_type_and_visibility=current_object->type_and_visibility;
	previous_skidding_volume=skidding_volume;

	explosion_detection_enabled=1;	
	gorilla_audio_update();
}

void audio_play_effect(int effect_index) {
	printf("** sound effect callback %d\n",effect_index);
}


