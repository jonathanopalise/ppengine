#include "ppengine/sub/framehandler/808.h"
#include "ppengine/sub/common/1572.h"
#include "ppengine/sub/common/bc6.h"
#include "ppengine/sub/common/1ff0.h"
#include "ppengine/sub2/functionqueue.h"
#include "ppengine/engine.h"

static void update_qualifying_starting_lights();

void frame_handler_852() {
	common_1572();
	common_bc6();
	common_1ff0();
	update_qualifying_starting_lights();
	if (ticks_remaining!=0) {
		// loc_86c
		ticks_remaining--;
		if (ticks_remaining==0) {
			jump_table_subfunction_number++;
			queue_sub2_function(4);
			high_precision_speed=0;
			player_car_stopped_at_session_end=0;
			car_slowdown_factor=0;
			unknown_81be=0;
			seconds_into_session=0;
			qualifying_complete_flag=0;
			qualifying_engine_started=1;
			session_engine_started=1;
			cars_passing_tracking_enabled=1;
			// TODO: work out what message is written by this call to DISPLAY_MESSAGE_CONTROL_EMBEDDED
		}
	} else {
		ticks_remaining=80;
	}
}

static void update_qualifying_starting_lights() {
	if (ticks_remaining==1) {
		gantry_and_starting_lights_appearance=4;
		//sample_player_2=3;
        sound_effect_callback(13);
	}
}

