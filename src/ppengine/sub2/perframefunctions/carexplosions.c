#include <inttypes.h>
#include "ppengine/sub2/perframefunctions/carexplosions.h"
#include "ppengine/engine.h"

void update_car_explosions() {
	struct movingobject *current_object;
	int objects_remaining;

	objects_remaining=7;
	current_object=moving_objects;
	while (objects_remaining>0) {
		if ((current_object->type_and_visibility&0xff)==3) {
			current_object->explosion_countdown-=20;
			if (current_object->explosion_countdown<0) {
				current_object->type_and_visibility=2;
			}
		}
		objects_remaining--;
		current_object++;
	}

	current_object=&moving_objects[PLAYER_CAR_OBJECT_INDEX];
	if ((current_object->type_and_visibility&0xff)==4) {
		current_object->one_time_speed_modification+=16;
		if (current_object->one_time_speed_modification>2080) {
			current_object->type_and_visibility=0x8001;
			clipped_steering_candidate_2=0;
			clipped_steering=0;
		} else {
			if ((current_object->one_time_speed_modification>>4)>=100) {
				current_object->type_and_visibility=4;
				// loc_1eac
			} else {
				// TODO: animation frame stuff?
				current_object->type_and_visibility=0x8004;
			}	
		}
	}
}


