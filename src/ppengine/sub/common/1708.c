#include <stdio.h>
#include "ppengine/sub/common/1708.h"
#include "ppengine/sub/data/race_seconds_lookup.h"
#include "ppengine/engine.h"

void common_1708() {
	int16_t lap_completion_events_counted_temp;
	uint16_t seconds_to_add;	
	if (new_lap_just_started) {
		lap_completion_events_counted_temp=lap_completion_events_counted-5;
		if (lap_completion_events_counted_temp>=0) {
			seconds_to_add=race_seconds_lookup[((((lap_completion_events_counted_temp+1)&3)*2)|((race_initial_timer_switch_2&7)<<3)|((race_initial_timer_switch_1&1)<<6))>>1];
			if ((seconds_to_add!=0) && (seconds_to_add<=100)) {
				seconds_remaining+=seconds_to_add;
				number_of_cpu_cars_in_use++;
				if (number_of_cpu_cars_in_use>7) {
					number_of_cpu_cars_in_use=7;
				}
				if (((race_initial_timer_switch_1&1)==0) && (lap_completion_events_counted==5)) {
					number_of_cpu_cars_in_use++;
				}
                sound_effect_callback(7);  // extended play beeps
				extended_play_frames_remaining=127;
				current_race_lap++;
			}
		}
	}
}


