#include "ppengine/sub/framehandler/66a.h"
#include "ppengine/sub/common/6a8.h"
#include "ppengine/sub2/functionqueue.h"
#include "ppengine/engine.h"

void frame_handler_66a() {
	queue_sub2_function(5);
	sample_player_1=2;
	lap_time_bcd_displayed_outside_gameplay=0;
	displayed_speed_outside_gameplay=0;
	current_score_outside_gameplay_bcd=0;
	current_race_lap=0;
	unknown_8020=0;

	common_6a8();
}

