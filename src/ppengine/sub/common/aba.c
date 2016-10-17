#include <stdio.h>
#include "ppengine/sub/common/aba.h"
#include "ppengine/sub/common/1572.h"
#include "ppengine/sub/common/bc6.h"
#include "ppengine/sub/common/1ff0.h"
#include "ppengine/sub/common/1406.h"
#include "ppengine/engine.h"
#include "ppengine/sub2/functionqueue.h"

void common_1364();
void common_13de();

void common_aba() {
	common_1572();
	common_bc6();
	common_1ff0();
	common_1406();
	common_1364();
	common_13de();
	if (ticks_remaining>0) {
		// loc_ad6
		ticks_remaining--;
		if (ticks_remaining==0) {
			jump_table_subfunction_number++;
			queue_sub2_function(0x2);
			high_precision_speed=0;
			player_car_stopped_at_session_end=0;
			car_slowdown_factor=0;
			unknown_81be=0;
			seconds_into_session=0;
			qualifying_complete_flag=0;
			cars_passed=0;
			session_engine_started=1;
			qualifying_session_state=1;
			cars_passing_tracking_enabled=1;
		}
	} else {
		ticks_remaining=0xf0;
	}
}

void common_1364() {
	if (ticks_remaining==0xb4) {
		// loc_1392
		gantry_and_starting_lights_appearance=1;
		//sample_player_2|=16; // sound 12 - 00000000 00010000
		sound_effect_callback(12);	// sample_player_2|16
	} else if (ticks_remaining==0x78) {
		// loc_13a4
		gantry_and_starting_lights_appearance=2;
		sound_effect_callback(12); // sample_player_2|16
	} else if (ticks_remaining==0x3c) {
		// loc_13b6
		gantry_and_starting_lights_appearance=3;
		sound_effect_callback(12); // sample_player_2|16
	} else if (ticks_remaining==1) {
		gantry_and_starting_lights_appearance=4;
		sound_effect_callback(13); // sample_player_2|8
	}
}

void common_13de() {
	if ((ticks_remaining>0) && (ticks_remaining<0xc8)) {
		if ((ticks_remaining<=0x1e) || (ticks_remaining&16)) {
			moving_objects[11].type_and_visibility=0x8001;
		} else {
			moving_objects[11].type_and_visibility=0x0001;
		}
	}
}



