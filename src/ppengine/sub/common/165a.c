#include "ppengine/sub/common/165a.h"
#include "ppengine/sub/data/required_qualifying_times.h"
#include "ppengine/engine.h"
#include <stdio.h>

void common_165a() {
	uint16_t potential_qualifying_position_minus_one; // r7
	uint16_t times_remaining_to_test; // r8
	uint16_t required_qualifying_times_index; // r9 (but without 3d94 added)
	uint16_t qualifying_time; // r3
	uint16_t qualifying_position_matched;

	if (new_lap_just_started) {
		if (qualifying_engine_started) {
			// loc_166e
			if (scoring_enabled_flag) {
				// loc_167c
				if ((current_lap_time_bcd>>16)==0) {
					qualifying_time=current_lap_time_bcd&0x0000ffff;
					times_remaining_to_test=8;
					required_qualifying_times_index=(required_qualifying_times_switch&7)<<3;
					qualifying_position_matched=0;
					potential_qualifying_position_minus_one=0;
					while ((times_remaining_to_test>0) && (!qualifying_position_matched)) {
						//printf("compare lap time %x with qualifying threshold %x\n",qualifying_time,required_qualifying_times[required_qualifying_times_index]);
						if (qualifying_time<=required_qualifying_times[required_qualifying_times_index]) {
							qualifying_position_matched=1;
							qualifying_position_minus_one=potential_qualifying_position_minus_one;
							scoring_enabled_flag=0;
							qualifying_complete_flag=1;
							//printf("qualifying time matched! set qualifying_position_minus_one to %d\n",qualifying_position_minus_one);
						} else {
							potential_qualifying_position_minus_one++;
							required_qualifying_times_index++;
							times_remaining_to_test--;
						}
					}
				}
			} else {
				scoring_enabled_flag=1;
			}
		} else {
			scoring_enabled_flag=1;
		}
	}
}


