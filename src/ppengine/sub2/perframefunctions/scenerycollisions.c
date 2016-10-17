#include <inttypes.h>
#include "ppengine/sub2/perframefunctions/scenerycollisions.h"
#include "ppengine/engine.h"

void check_scenery_collisions() {
	struct sceneryobject *current_object;
	int objects_remaining;

	if ((cars_passing_tracking_enabled) && 
        (moving_objects[PLAYER_CAR_OBJECT_INDEX].type_and_visibility==0x8001) &&
		(post_respawn_countdown==0)) {
		current_object=scenery_objects;
		objects_remaining=24;
		while ((objects_remaining>0) && (post_respawn_countdown==0)) {
			if ((current_object->player_forward_position_difference>=-20) &&
                (current_object->player_forward_position_difference<=20) &&
                (current_object->player_sideways_position_difference>=-900) &&
                (current_object->player_sideways_position_difference<=900)) {
				moving_objects[PLAYER_CAR_OBJECT_INDEX].type_and_visibility=0x8004;
				moving_objects[PLAYER_CAR_OBJECT_INDEX].one_time_speed_modification=0;
				post_respawn_countdown=150;
				if (!waiting_for_coin) {
					unknown_80e2=5;
				}

			}
			objects_remaining--;
			current_object++;
		}
	}
}


