#include <inttypes.h>
#include <stdlib.h>
#include "ppengine/sub2/perframefunctions/carcollisions.h"
#include "ppengine/engine.h"

void check_car_collisions() {
	struct movingobject *current_object;
	int objects_remaining;
	int32_t r0;
	int32_t r1;

	r1=0; // TODO: this doesn't appear to be set in this sub before it gets read?
	objects_remaining=7;
	current_object=moving_objects;
	if (cars_passing_tracking_enabled) {
		while (objects_remaining>0) {
			if (current_object->type_and_visibility==0x8002) {
				r0=current_object->player_forward_position_difference-0x1a;
				if (r0<-38) {
					// 1cbe
					if (r1<=900) {
						current_object->one_time_speed_modification=-7000;
					}	
				} else {
					if (r0<=56) {
						r1=abs(current_object->player_sideways_position_difference);
						if (r1<=700) {
							if (r0>38) {
								// loc_1ccc
								if (seconds_into_session>=15) {
									current_object->one_time_speed_modification=7000;
								}
								if (car_slowdown_factor==0) {
									car_slowdown_factor=55;
								}
							} else {
								if (current_object->player_sideways_position_difference<0) {
									opponent_car_grinding_sideways_movement=-1;
								} else {
									opponent_car_grinding_sideways_movement=1;
								}
								if (r1>500) {
									// loc_1cda
									if (car_slowdown_factor==0) {
										car_slowdown_factor=55;
									}
								} else {
									current_object->type_and_visibility=0x8003;
									current_object->explosion_countdown=0x7ff;
									if (moving_objects[PLAYER_CAR_OBJECT_INDEX].type_and_visibility!=0x8004) {
										moving_objects[PLAYER_CAR_OBJECT_INDEX].type_and_visibility=0x8004;

										// note that one_time_speed_modification for PLAYER_CAR_OBJECT_INDEX
										// is in fact an explosion countdown timer
										moving_objects[PLAYER_CAR_OBJECT_INDEX].one_time_speed_modification=0;
										if (!waiting_for_coin) {
											unknown_80e2=5;
										}
									}
								}
							}
						}
					}
				}
			}
			objects_remaining--;
			current_object++;
		}

		if (moving_objects[PLAYER_CAR_OBJECT_INDEX].type_and_visibility==0x8001) {
			if (post_respawn_countdown>0) {
				post_respawn_countdown--;
			} else {
				if (current_object->type_and_visibility==0x8006) {
					// i think this is the collision detection with the gantry
					if ((current_object->player_forward_position_difference>=-20) && 
                        (current_object->player_forward_position_difference<=20) &&
                        (abs(current_object->player_sideways_position_difference)>=1536)) {
						moving_objects[PLAYER_CAR_OBJECT_INDEX].type_and_visibility=0x8004;
						moving_objects[PLAYER_CAR_OBJECT_INDEX].one_time_speed_modification=0;
						post_respawn_countdown=150;
						if (!waiting_for_coin) {
							unknown_80e2=5;
						}
					}
				}
			}
		}
	}
}


