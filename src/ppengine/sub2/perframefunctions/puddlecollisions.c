#include "ppengine/engine.h"

void check_puddle_collisions() {
	struct movingobject *current_object;
	int objects_remaining;
	int16_t car_slowdown_factor_change;

	objects_remaining=3;
	current_object=&moving_objects[8];
	while (objects_remaining>0) {
		if (current_object->type_and_visibility==0x8007) {
			if (current_object->player_forward_position_difference>47 && 
                current_object->player_forward_position_difference<208 &&
				current_object->player_sideways_position_difference>-1000 &&
				current_object->player_sideways_position_difference<1000) {
				if (car_slowdown_factor>=0) {
					car_slowdown_factor_change=((current_speed_8_bit_candidate_3>>16)-30)-(internal_accel_pedal<<3);
					if (car_slowdown_factor_change>0) {
						car_slowdown_factor+=car_slowdown_factor_change;
					}
				}
				// loc_1df6
				// TODO: play puddle splash sound but has some additional logic
			} else {
				// loc_1e20
				current_object->explosion_countdown=0;
			}
		}
		objects_remaining--;
		current_object++;
	}
}


