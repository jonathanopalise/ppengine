#include "ppengine/sub2/perframefunctions/cpucarai.h"
#include "ppengine/engine.h"

void run_cpu_car_ai() { // 1A3E
	int16_t unknown;

	int32_t r0;
	uint16_t r7;
	uint16_t r8;
	uint16_t r9;
	uint16_t r10;
	uint16_t r11;

	struct movingobject *outer_current_object;
	struct movingobject *inner_current_object;
	int outer_objects_remaining;
	int inner_objects_remaining;
	int inner_offset;
	int outer_offset; 

	int16_t forward_position_difference; // r1
	int16_t speed_difference; // r3
	int action_taken;

	uint16_t sideways_position_difference;
	uint16_t old_sideways_position_difference;
	int32_t outer_current_object_speed;

	// sub_1a3e
	unknown=seconds_into_session-10;
	if (unknown>=0) {
		unknown+=1;
		if (unknown>40) {
			unknown=40;
		}
		// loc_1a52
		unknown*=20;
		r7=unknown;
		unknown>>=1;
		r8=unknown;
		unknown>>=1;
		r9=unknown;
		unknown>>=1;
		r10=unknown;
		unknown>>=3;
		r11=unknown+1;
		outer_objects_remaining=6;
		outer_offset=0;
		outer_current_object=moving_objects;
		while (outer_objects_remaining>0) {
			inner_objects_remaining=outer_objects_remaining;
			// loc_1a7a
			if ((outer_current_object->type_and_visibility==0x8002) && (outer_current_object->maximum_speed!=0))  {
				inner_current_object=outer_current_object;
				inner_offset=outer_offset;
				inner_current_object++;
				inner_offset++;
				outer_current_object_speed=outer_current_object->current_speed;
				while (inner_objects_remaining>0) {
					// loc_1a9a 
					if (inner_current_object->type_and_visibility==0x8002) {
						forward_position_difference=((outer_current_object->forward_position>>16)-(inner_current_object->forward_position>>16))+r8;
						if (r7>(uint16_t)forward_position_difference) {
							sideways_position_difference=outer_current_object->sideways_position-inner_current_object->sideways_position+800;
							old_sideways_position_difference=sideways_position_difference;
							sideways_position_difference-=1600;
							if (sideways_position_difference>old_sideways_position_difference) {
								speed_difference=(outer_current_object_speed>>16)-(inner_current_object->current_speed>>16);
								action_taken=0;
								forward_position_difference-=r10;
								if (forward_position_difference<0) {
									action_taken=1;
									// loc_1aee
									if ((speed_difference>=15) && (outer_current_object->sideways_movement==0)) {
										outer_current_object->sideways_movement=-outer_current_object->sideways_position;
									}
								}
								forward_position_difference-=r9;
								if ((!action_taken) && (forward_position_difference<0)) {
									action_taken=1;
									// loc_1b14
									if (speed_difference>-20) {
										outer_current_object->one_time_speed_modification=-30000;
										inner_current_object->one_time_speed_modification=20000;
									}
								}
								forward_position_difference-=r10;
								if ((!action_taken) && (forward_position_difference<0)) {
									action_taken=1;
									// loc_1b28
									if (speed_difference>-15) {
										r0=(inner_current_object->current_speed>>16)+r11;
										inner_current_object->current_speed=(inner_current_object->current_speed&0xffff)|(r0<<16);
										r0-=r11*2;
										if (r0<0) {
											r0=0;
										}
										outer_current_object->current_speed=(outer_current_object->current_speed&0xffff)|(r0<<16);
									}
								}
								forward_position_difference-=r10;
								if ((!action_taken) && (forward_position_difference<0)) {
									action_taken=1;
									// loc_1b46
									if (speed_difference<15) {
										r0=(outer_current_object->current_speed>>16)+r11;
										outer_current_object->current_speed=(outer_current_object->current_speed&0xffff)|(r0<<16);
										r0-=r11*2;
										if (r0<0) {
											r0=0;
										}
										inner_current_object->current_speed=(inner_current_object->current_speed&0xffff)|(r0<<16);
									}
								}
								forward_position_difference-=r9;
								if ((!action_taken) && (forward_position_difference<0)) {
									action_taken=1;
									// loc_1b64
									if (speed_difference<20) {
										outer_current_object->one_time_speed_modification=20000;
										inner_current_object->one_time_speed_modification=-30000;
									}
								}
								if ((!action_taken) && (speed_difference<=-15) && (inner_current_object->sideways_movement==0)) {
									inner_current_object->sideways_movement=-inner_current_object->sideways_position;	
								}
							}
						}
					}
					// loc_1b04
					inner_current_object++;
					inner_offset++;
					inner_objects_remaining--;
				}
			}
			// loc_1b0a
			outer_current_object++;
			outer_offset++;
			outer_objects_remaining--;
		}
	}
}

