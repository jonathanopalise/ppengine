#include <inttypes.h>
#include "ppengine/sub/common/148e.h"
#include "ppengine/engine.h"

void common_1494();
void common_14cc(int16_t r1);

void common_148e() {
	if (car_slowdown_factor==0) {
		// loc_1494
		common_1494();
	} else {
		// loc_14ac
		if (car_slowdown_factor<0) {
			if (-car_slowdown_factor+(current_speed_8_bit_candidate_3>>16)<150) {
				common_1494();
			} else {
				common_14cc(car_slowdown_factor);
			}
		} else {
			common_14cc(-car_slowdown_factor);
		}
		car_slowdown_factor=0;
	}
}

void common_1494() {
	current_speed_8_bit_candidate_3=((((high_precision_speed<<8)/625)&0xffff)<<12);
}

void common_14cc(int16_t r1) {
	// loc_14cc
	current_speed_8_bit_candidate_3+=(r1<<10);
	if (current_speed_8_bit_candidate_3<0) {
		current_speed_8_bit_candidate_3=0;
	}
	high_precision_speed=((current_speed_8_bit_candidate_3>>16)*10000)>>8;
	if (high_precision_speed>=0) {
		if ((current_speed_8_bit_candidate_3>>16)>=256) {
			current_speed_8_bit_candidate_3&=0x0000ffff;
			current_speed_8_bit_candidate_3|=0x00ff0000;
		}
	} else {
		// loc_1500
		current_speed_8_bit_candidate_3=0;
	}
}
