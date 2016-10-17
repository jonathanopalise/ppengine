#include "ppengine/sub2/queuedfunctions/554.h"
#include "ppengine/engine.h"

void queued_function_554() {
	struct movingobject *current_moving_object;
	int moving_objects_remaining;
	int initial_maximum_speed_decision_maker;
	uint16_t current_maximum_speed;

	current_maximum_speed=((qualifying_position_minus_one&7)*0x300)+0x5400;
	initial_maximum_speed_decision_maker=race_initial_timer_switch_2&7;
	if (initial_maximum_speed_decision_maker<6) {
		current_maximum_speed+=0x800;
	}
	if (initial_maximum_speed_decision_maker<4) {
		current_maximum_speed+=0x400;
	}

	current_moving_object=moving_objects;
	moving_objects_remaining=7;
	while (moving_objects_remaining>0) {
		current_moving_object->maximum_speed=current_maximum_speed;
		current_maximum_speed-=0x800;
		current_moving_object++;
		moving_objects_remaining--;
	}

	slow_cpu_cars_ahead=10;
}
