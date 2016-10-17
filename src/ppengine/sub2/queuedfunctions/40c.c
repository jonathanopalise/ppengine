#include "ppengine/sub2/queuedfunctions/40c.h"
#include "ppengine/engine.h"

void queued_function_40c() {
	gantry_and_starting_lights_appearance=0;

	struct movingobject *current_moving_object;
	int moving_objects_remaining;
	current_moving_object=moving_objects;
	moving_objects_remaining=7;
	while (moving_objects_remaining>0) {
		current_moving_object->type_and_visibility=0x2;
		current_moving_object++;
		moving_objects_remaining--;
	}
	high_precision_sideways_position=0xfe00;
	forward_position=(forward_position&0xffff)|0xff000000;
	current_speed_8_bit_candidate_3&=0xffff;
	steering_or_car_orientation=0;
	steering_wheel_rotation_candidate_2=steering_wheel_rotation;
	moving_objects[PLAYER_CAR_OBJECT_INDEX].player_forward_position_difference=0x10;
}
