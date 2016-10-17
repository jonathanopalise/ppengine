#include <stdlib.h>
#include "ppengine/sub/common/1b2e.h"
#include "ppengine/sub/common/1b92.h"
#include "ppengine/sub/common/1786.h"
#include "ppengine/sub/common/1ba4.h"
#include "ppengine/engine.h"

void common_1b72();

void common_1b2e() {
	int16_t absolute_high_precision_sideways_position;

	common_1b72();
	common_1b92();
	common_1786();
	common_1ba4();
	off_track_sound_effect_pitch=0;
	if (car_slowdown_factor==0) {
		absolute_high_precision_sideways_position=abs(high_precision_sideways_position);

		// loc_1b4c
		if (absolute_high_precision_sideways_position>0x4c00) {
			car_slowdown_factor=(0-(absolute_high_precision_sideways_position-0x2000))>>8;
			if (!waiting_for_coin) {
				off_track_sound_effect_pitch=(-car_slowdown_factor)>>3;
			}
		}
	}
}

void common_1b72() {
	uint16_t qualifying_ended_slow_down;

	qualifying_ended_slow_down=0;
	if (qualifying_complete_flag) {
		qualifying_ended_slow_down=1;
	} else {
		if (seconds_remaining==0) {
			qualifying_ended_slow_down=1;
		}
	}

	if (qualifying_ended_slow_down) {
		car_slowdown_factor=0xfed4;
		if ((current_speed_8_bit_candidate_3>>16)==0) {
			player_car_stopped_at_session_end=1;
		}
	}
}


