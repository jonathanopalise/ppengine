#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include "ppengine/sub2/perframefunctions/cpucarspawning.h"
#include "ppengine/sub2/perframefunctions/common/random.h"
#include "ppengine/engine.h"

void activate_cpu_car(struct movingobject *object, uint16_t current_speed, uint16_t forward_position);

void spawn_new_cpu_cars() {
	uint16_t objects_remaining; // r12 
	struct movingobject *current_object;

	uint32_t player_forward_position_high_word=forward_position>>16;
	uint32_t player_speed_high_word=current_speed_8_bit_candidate_3>>16;

	if (cpu_car_spawning_mode==1) {
		// loc_19a6
		if (seconds_into_session>15) {
			objects_remaining=number_of_cpu_cars_in_use&7;
			if (objects_remaining==0) {
				objects_remaining++;
			}
			current_object=&moving_objects[6];
			while (objects_remaining>0) {
				if ((current_object->type_and_visibility&0x8000)==0) {
					if ((slow_cpu_cars_ahead!=0) || ((current_speed_8_bit_candidate_3>>16)>=0x8c) || (abs(moving_objects[PLAYER_CAR_OBJECT_INDEX].sideways_position)<50)) {
						if (slow_cpu_cars_ahead!=0) {
							slow_cpu_cars_ahead--;
						}
						//printf("spawning mode 1: activate cpu car ahead of player (seconds into session is %d)\n",seconds_into_session);
						activate_cpu_car(current_object,player_speed_high_word>>1,player_forward_position_high_word+4096);
					} else {
						if (moving_objects[PLAYER_CAR_OBJECT_INDEX].sideways_position>0) {
							current_object->sideways_position=-816;
						} else {
							current_object->sideways_position=816;
						}
						activate_cpu_car(current_object,player_speed_high_word+70,player_forward_position_high_word-58);
						//printf("spawning mode 1: activate cpu car behind player (seconds into session is %d)\n",seconds_into_session);
						slow_cpu_cars_ahead=5;
					}
				}
				current_object--;
				objects_remaining--;
			}
		}
	} else if (cpu_car_spawning_mode==-1) {
		objects_remaining=number_of_cpu_cars_in_use&7;
		if (objects_remaining==0) {
			objects_remaining++;
		}
		current_object=&moving_objects[6];
		while (objects_remaining>0) {
			if ((current_object->type_and_visibility&0x8000)==0) {
				update_pseudorandom_number();
				//printf("spawning mode -1: activate cpu car behind player\n");
				activate_cpu_car(current_object,(pseudorandom_number&53)+100,player_forward_position_high_word-58);
			}
			current_object--;
			objects_remaining--;
		}
	}
}

void activate_cpu_car(struct movingobject *object, uint16_t current_speed, uint16_t forward_position) {
	object->current_speed&=0xffff;
	object->current_speed|=current_speed<<16;
	object->forward_position&=0xffff;
	object->forward_position|=forward_position<<16;
	object->type_and_visibility=0x8002;
}
