#include <stdio.h>
#include "ppengine/sub2/queuedfunctions/476.h"
#include "ppengine/engine.h"

#define CPU_CAR_LEFT_POSITION 576
#define CPU_CAR_RIGHT_POSITION -768

#define PLAYER_CAR_LEFT_POSITION -7680
#define PLAYER_CAR_RIGHT_POSITION 9728

void position_player_car(uint16_t player_forward_position,int16_t player_high_precision_sideways_position);
void position_cpu_car(struct movingobject *cpu_car, uint16_t forward_position_high_word,int16_t sideways_position);

void queued_function_476() {
	/* we ignore the calls to the following as the responsibilities they cover
       should be handled by the graphics engine:

       - INITIALISE_VISIBLE_BACKGROUND
       - SUB_2B0
       - UPDATE_ROAD_MEMORY_FULL
       - WRITE_STATUS_DISPLAY_CAPTIONS
	*/

	struct movingobject *current_moving_object;
	int moving_objects_remaining;
	uint16_t current_forward_positioning_point;
	uint16_t current_qualifying_position_minus_one;
	int player_car_positioned;
	uint16_t *current_puddle;

	gantry_and_starting_lights_appearance=0;

	// puddles

	uint16_t puddle_data[]={0x8d32,0xa5ce,0xe032};

	current_puddle=&puddle_data[2];	
	current_moving_object=&moving_objects[8];
	moving_objects_remaining=3;
	while (moving_objects_remaining>0) {
		current_moving_object->type_and_visibility=0x8007;
		current_moving_object->forward_position=((*current_puddle)&0xff00)<<16;
		current_moving_object->sideways_position=((int16_t)((*current_puddle)<<8))>>4;
		//printf("** setup race puddle forward = %d, sideways = %d\n",current_moving_object->forward_position,current_moving_object->sideways_position);
		current_moving_object++;
		moving_objects_remaining--;
		current_puddle--;
	}

	//printf("positioning cars on grid. qualifying position is %d\n",qualifying_position_minus_one);

	current_moving_object=moving_objects;
	moving_objects_remaining=7;
	while (moving_objects_remaining>0) {
		current_moving_object->type_and_visibility=0x2;
		current_moving_object++;
		moving_objects_remaining--;
	}

	// sub_496
	current_moving_object=moving_objects;
	current_forward_positioning_point=0;
	current_qualifying_position_minus_one=0;
	player_car_positioned=0;
	while (!player_car_positioned) {
		if (current_qualifying_position_minus_one==qualifying_position_minus_one) {
			// player on right, cpu on left
			player_car_positioned=1;
			position_player_car(current_forward_positioning_point,PLAYER_CAR_RIGHT_POSITION);
			position_cpu_car(current_moving_object,current_forward_positioning_point,CPU_CAR_LEFT_POSITION);
			current_moving_object++;			
		} else if ((current_qualifying_position_minus_one+1)==qualifying_position_minus_one) {
			// player on left, cpu on right
			player_car_positioned=1;
			position_player_car(current_forward_positioning_point,PLAYER_CAR_LEFT_POSITION);
			position_cpu_car(current_moving_object,current_forward_positioning_point,CPU_CAR_RIGHT_POSITION);
			current_moving_object++;			
		} else {
			// cpu on left and right
			position_cpu_car(current_moving_object,current_forward_positioning_point,CPU_CAR_RIGHT_POSITION);
			current_moving_object++;			
			position_cpu_car(current_moving_object,current_forward_positioning_point,CPU_CAR_LEFT_POSITION);
			current_moving_object++;			
		}
		current_qualifying_position_minus_one+=2;
		current_forward_positioning_point-=128;
	}
}

void position_player_car(uint16_t player_forward_position_high_word,int16_t player_high_precision_sideways_position) {
	//printf("positioning player car at %d, %d\n",player_forward_position_high_word, player_high_precision_sideways_position);
	high_precision_sideways_position=player_high_precision_sideways_position;
	forward_position=(player_forward_position_high_word-18)<<16;
	current_speed_8_bit_candidate_3=0;
	steering_or_car_orientation=0;
	steering_wheel_rotation_candidate_2=steering_wheel_rotation;
	moving_objects[PLAYER_CAR_OBJECT_INDEX].type_and_visibility=0x8001;
	moving_objects[PLAYER_CAR_OBJECT_INDEX].player_forward_position_difference=16;
}

void position_cpu_car(struct movingobject *cpu_car, uint16_t forward_position_high_word,int16_t sideways_position) {
	//printf("positioning cpu car at %d, %d\n",forward_position_high_word, sideways_position);
	cpu_car->forward_position=forward_position_high_word<<16;
	cpu_car->sideways_position=sideways_position;
	cpu_car->current_speed=0;
	cpu_car->maximum_speed=0;
	cpu_car->one_time_speed_modification=0;
	cpu_car->sideways_movement=0;
	cpu_car->type_and_visibility=0x8002;
}
