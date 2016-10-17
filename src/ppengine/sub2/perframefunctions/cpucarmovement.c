#include <inttypes.h>
#include <stdlib.h>
#include "ppengine/sub2/perframefunctions/cpucarmovement.h"
#include "ppengine/sub2/data/sub_1886_lookup.h"
#include "ppengine/engine.h"

void update_cpu_car_speed(struct movingobject *current_object);
void update_cpu_car_sideways_position(struct movingobject *current_object);
void sub_1886(struct movingobject *current_object, uint16_t current_object_address);

void update_cpu_car_positions() { // 1784
	int objects_remaining; // r10
	struct movingobject *current_object; // r11
	uint16_t current_object_address;

	objects_remaining=7;
	current_object=moving_objects;

	current_object_address=0x8b00;
	while (objects_remaining>0) {
		if (current_object->type_and_visibility&0x8000) {
			current_object->display_variant=((current_object_address>>4)&0xc)|((current_object->forward_position>>16)&1);
			update_cpu_car_speed(current_object);
			update_cpu_car_sideways_position(current_object);
			sub_1886(current_object,current_object_address);
			current_object->forward_position+=current_object->current_speed>>3;
		}
		objects_remaining--;
		current_object++;
		current_object_address+=0x20;
	}
}

void update_cpu_car_speed(struct movingobject *current_object) {
	uint16_t maximum_speed_copy;

	maximum_speed_copy=current_object->maximum_speed;
	if (current_object->type_and_visibility==0x8003) {
		// loc_1814 - reduce exploding cpu car speed
		current_object->current_speed-=200000;
		if (current_object->current_speed<0) {
			current_object->current_speed=0;
		}
	} else if (current_object->one_time_speed_modification!=0) {
		// loc_1824 - parse cpu car speed change
		current_object->current_speed+=current_object->one_time_speed_modification<<5;
		if (current_object->current_speed<0) {
			current_object->current_speed=0;
		}
		current_object->one_time_speed_modification=0;
	} else {
		if ((current_object->current_speed>>16)>=current_object->unknown_attribute) {
			// loc_1806
			if ((current_object->current_speed>>16)>(current_object->unknown_attribute+10)) {
				maximum_speed_copy+=current_object->maximum_speed;
				current_object->current_speed-=maximum_speed_copy;
			}
		} else if ((current_object->current_speed>>16)>=0x6e) {
			// loc_1802
			current_object->current_speed+=maximum_speed_copy;
		} else {
			if (seconds_into_session<10) {
				current_object->current_speed+=maximum_speed_copy;
			}
			// loc_1800
			maximum_speed_copy+=maximum_speed_copy;
			current_object->current_speed+=maximum_speed_copy;
		}
	}
}

void update_cpu_car_sideways_position(struct movingobject *current_object) {
	if (current_object->sideways_movement!=0) {
		if (current_object->sideways_movement<0) {
			current_object->sideways_position+=current_object->sideways_movement>>6;
			if (current_object->sideways_position<-768) {
				current_object->sideways_movement=0;
			}
		} else {
			current_object->sideways_position+=(current_object->sideways_movement>>6)+1;
			if (current_object->sideways_position>768) {
				current_object->sideways_movement=0;
			}
		}
	}
}

void sub_1886(struct movingobject *current_object, uint16_t current_object_address) {
	uint16_t r0;
	uint16_t r3;
	int16_t r2;
	uint8_t r1;

	r1=((current_object->forward_position>>24)+5)&0xff;
	r3=4;
	r0=0;

	// loc_1896
	while (r3>0) {
		r2=abs(sub_1886_lookup[r1]);
		r0+=r2;
		r1++;
		r3--;
	}
	r0=(~(r0>>1))&0xff;
	r2=(((~current_object_address)&0xe0)>>3);
	r0+=r2;
	r2>>=1;
	r0+=r2;
	r2=current_speed_8_bit_candidate_3>>18;
	r0+=r2;
	r2>>=1;
	r0+=r2;
	r2=seconds_into_session>>2;
	r0+=r2;
	r2>>=1;
	r0+=r2;
	r2=race_initial_timer_switch_2&7;
	if (r2<4) {
		// loc_1916
		r0-=0x8c;
		if (r0<0x32) {
			// loc_192c
			r0=0x32;
		} else if (r0>0xd2) {
			r0=0xd2;
		}
	} else if (r2<6) {
		// loc_1932
		r0-=0xaa;
		if (r0<0x28) {
			// loc_1948
			r0=0x28;
		} else if (r0>0xa0) {
			r0=0xa0;
		}
	} else {
		r0-=0xb4;
		if (r0<0x1e) {
			// loc_1910
			r0=0x1e;
		} else if (r0>0x96) {
			r0=0x96;
		}
	}
	current_object->unknown_attribute=r0;
}

