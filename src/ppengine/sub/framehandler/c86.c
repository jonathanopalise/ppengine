#include "ppengine/sub/framehandler/c86.h"
#include "ppengine/sub/common/bc8.h"
#include "ppengine/sub/common/18dc.h"
#include "ppengine/sub/common/12a2.h"
#include "ppengine/sub/common/18f4.h"
#include "ppengine/engine.h"

int common_124c();

void frame_handler_c86() {
	//printf("c86: previous_lap_time_bcd is %x\n",previous_lap_time_bcd);
	common_bc8(); // update seconds remaining, laptime and speed in hud
	common_18dc(); // update score and high score in hud
	common_12a2(); // update passing bonus and time bonus in hud
	if (common_124c()>0) {
		//jump_table_function_number=4;
		//jump_table_subfunction_number=0;
		jump_table_function_number=1;
		jump_table_subfunction_number=1;
	}
}

int common_124c() {
	uint32_t score_to_add;

	frames_until_next_countdown_update--;
	if (frames_until_next_countdown_update==0) {
		frames_until_next_countdown_update=8;
		if (cars_passed==0) {
			// loc_1272
			if (time_bonus<=0) {
				// loc_129c
				return 1;
			} else {
				time_bonus--;
				seconds_remaining=time_bonus;
				sample_player_2|=128;
				score_to_add=0x20000;
			}
		} else {
			cars_passed--;
			sample_player_2|=2;
			score_to_add=0x5000;
		}
		// loc_1290
		current_score_times_100_bcd=common_18f4(current_score_times_100_bcd,score_to_add);
	}
	return 0;
}
