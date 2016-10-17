#include "ppengine/sub2/perframefunctions/cpucarhiding.h"
#include "ppengine/sub2/perframefunctions/common/random.h"
#include "ppengine/engine.h"
#include <stdlib.h>

void hide_car_and_increment_passed_counter(struct movingobject *object);

void hide_out_of_sight_cpu_cars() {
	struct movingobject *current_moving_object;
	struct sceneryobject *current_scenery_object;

	int objects_remaining;

	// loc_1b78
	objects_remaining=11;
	current_moving_object=moving_objects;
	while (objects_remaining>0) {
		current_moving_object->player_forward_position_difference=(current_moving_object->forward_position>>16)-(forward_position>>16);
		current_moving_object->player_sideways_position_difference=current_moving_object->sideways_position-moving_objects[PLAYER_CAR_OBJECT_INDEX].sideways_position;
		objects_remaining--;
		current_moving_object++;
	}
	current_moving_object++;
	current_moving_object->player_forward_position_difference=(current_moving_object->forward_position>>16)-(forward_position>>16);
	current_moving_object->player_sideways_position_difference=current_moving_object->sideways_position-moving_objects[PLAYER_CAR_OBJECT_INDEX].sideways_position;

	objects_remaining=24;
	current_scenery_object=scenery_objects;
	// loc_1bca
	while (objects_remaining) {
		current_scenery_object->player_forward_position_difference=current_scenery_object->forward_position-(forward_position>>16);
		current_scenery_object->player_sideways_position_difference=current_scenery_object->sideways_position-moving_objects[PLAYER_CAR_OBJECT_INDEX].sideways_position;
		objects_remaining--;
		current_scenery_object++;
	}

	objects_remaining=7;
	current_moving_object=moving_objects;
	// loc_1be8
	while (objects_remaining>0) {
		if (current_moving_object->type_and_visibility&0x8000) {
			if (current_moving_object->player_forward_position_difference<-300) {
				// 1c34 - cpu car passed
				hide_car_and_increment_passed_counter(current_moving_object);
			} else if (current_moving_object->player_forward_position_difference<-60) {
				// 1c26 - check cpu car blocked
				if ((current_moving_object->player_sideways_position_difference>-3000) &&
                    (current_moving_object->player_sideways_position_difference<3000)) {
					hide_car_and_increment_passed_counter(current_moving_object);
				}
			} else if (current_moving_object->player_forward_position_difference>=4608) {
				update_pseudorandom_number();
				if (pseudorandom_number&1) {
					current_moving_object->one_time_speed_modification=-30000;
					// TODO: make sure this line performs as intended
					current_moving_object->forward_position+=0xff000000;
				} else {
					// 1c42
					current_moving_object->type_and_visibility&=0x7fff;
				}
			}
		}
		objects_remaining--;
		current_moving_object++;
	}
}

void hide_car_and_increment_passed_counter(struct movingobject *object) {
	object->type_and_visibility&=0x7fff;
	if (cars_passing_tracking_enabled) {
		cars_passed++;
	}
}


