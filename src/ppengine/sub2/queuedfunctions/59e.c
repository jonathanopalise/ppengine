#include "ppengine/sub2/queuedfunctions/59e.h"
#include "ppengine/sub2/queuedfunctions/1e6.h"
#include "ppengine/sub2/queuedfunctions/24d8.h"
#include "ppengine/engine.h"

void queued_function_59e() {
	struct movingobject *current_moving_object;
	int moving_objects_remaining;

	// loc_63a

	current_moving_object=&moving_objects[8];
	moving_objects_remaining=3;
	while (moving_objects_remaining>0) {
		//printf("** setup qualifying puddle\n");
		current_moving_object->type_and_visibility=0x7;
		current_moving_object->forward_position=0x8800;
		current_moving_object->sideways_position=0;
		current_moving_object++;
		moving_objects_remaining--;
	}

	// set car positions

	current_moving_object=moving_objects;
	moving_objects_remaining=7;
	while (moving_objects_remaining>0) {
		current_moving_object->type_and_visibility=0x2;
		current_moving_object++;
		moving_objects_remaining--;
	}
	high_precision_sideways_position=-512;
	forward_position=(forward_position&0xffff)|0xff000000;
	current_speed_8_bit_candidate_3&=0xffff;
	steering_or_car_orientation=0;
	steering_wheel_rotation_candidate_2=steering_wheel_rotation;
	moving_objects[PLAYER_CAR_OBJECT_INDEX].type_and_visibility=0x8001;
	moving_objects[PLAYER_CAR_OBJECT_INDEX].player_forward_position_difference=16;
	queued_function_1e6();
	queued_function_24d8();
}
