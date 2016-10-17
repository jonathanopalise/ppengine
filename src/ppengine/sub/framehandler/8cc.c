#include "ppengine/sub/framehandler/8cc.h"
#include "ppengine/sub/common/148e.h"
#include "ppengine/sub/common/1572.h"
#include "ppengine/sub/common/1ff0.h"
#include "ppengine/sub/common/1906.h"
#include "ppengine/sub/common/1928.h"
#include "ppengine/sub/common/bc6.h"
#include "ppengine/sub/common/1b2e.h"
#include "ppengine/sub/common/165a.h"
#include "ppengine/sub/common/16be.h"
#include "ppengine/sub/data/qualifying_bonus_lookup.h"
#include "ppengine/sub2/functionqueue.h"
#include "ppengine/engine.h"

void frame_handler_8cc() {
	common_148e();
	common_1572();
	common_1ff0();
	common_1906();
	common_1928();
	common_bc6();  // bottleneck!
	common_1b2e();
	common_165a();
	common_16be();
	if (player_car_stopped_at_session_end) {
		moving_objects[PLAYER_CAR_OBJECT_INDEX].type_and_visibility=0x1;
		engine_sound_active=0;
		if (!qualifying_complete_flag) {
			// loc_9a2
			cars_passing_tracking_enabled=0;
			displayed_speed_outside_gameplay=session_top_speed_bcd;
			session_end_animation_ticks_remaining=600;
			jump_table_function_number=1;
			jump_table_subfunction_number=1;
			player_has_passed_start_line_in_current_session=0;
			if (lap_completion_events_counted==2) {
				previous_lap_time_display_ticks_remaining=600;
				current_lap_time_bcd=previous_lap_time_bcd;
				lap_time_bcd_displayed_outside_gameplay=previous_lap_time_bcd;
			}
		} else {
			jump_table_subfunction_number++;
			cars_passing_tracking_enabled=0;
			previous_lap_time_display_ticks_remaining=300;
			session_end_animation_ticks_remaining=300;
			qualifying_outcome_cycling_value_tracker=240;
			frames_until_next_countdown_update=8;
			qualifying_bonus=qualifying_bonus_lookup[qualifying_position_minus_one&7];
			if (qualifying_position_minus_one==0) {
				// loc_964
				sample_player_1=4;
			} else {
				sample_player_1=3;
			}
			queue_sub2_function(0x19);
			current_race_lap++;
		}
	}
}

