#include "ppengine/sub/framehandler/b2c.h"
#include "ppengine/sub/common/148e.h"
#include "ppengine/sub/common/1572.h"
#include "ppengine/sub/common/1ff0.h"
#include "ppengine/sub/common/1906.h"
#include "ppengine/sub/common/1928.h"
#include "ppengine/sub/common/199e.h"
#include "ppengine/sub/common/bc6.h"
#include "ppengine/sub/common/1b2e.h"
#include "ppengine/sub/common/165a.h"
#include "ppengine/sub/common/16be.h"
#include "ppengine/sub/common/1708.h"
#include "ppengine/lib/hud.h"
#include "ppengine/engine.h"

void common_1c14();

void frame_handler_b2c() {
	common_148e(); // apply slowdown factor to player car
	common_1572();
	common_1ff0();
	common_1906();
	common_1928();
	common_199e();
	common_bc6();
	common_1b2e();
	common_165a();
	common_16be();
	common_1708();
	common_1c14();

	if (full_race_distance_completed) {
		// loc_ba2
		jump_table_subfunction_number++;
		unknown_8282=current_speed_8_bit_candidate_3;
		cars_passing_tracking_enabled=0;
		cpu_car_spawning_mode=-1;
		unknown_82a6=1;
	} else if (player_car_stopped_at_session_end) {
		jump_table_subfunction_number+=3;
		time_bonus=-1;
		engine_sound_active=0;
		player_has_passed_start_line_in_current_session=0;
		cars_passing_tracking_enabled=0;
		moving_objects[PLAYER_CAR_OBJECT_INDEX].type_and_visibility=0x1;
		displayed_speed_outside_gameplay=session_top_speed;
		session_end_animation_ticks_remaining=600;
		if (lap_completion_events_counted!=4) {
			//printf("1c14: previous_lap_time_bcd set to %x\n",previous_lap_time_bcd);
			previous_lap_time_bcd=fastest_session_lap_bcd;
			current_lap_time_bcd=fastest_session_lap_bcd;
			lap_time_bcd_displayed_outside_gameplay=fastest_session_lap_bcd;
			previous_lap_time_display_ticks_remaining=600;
		}
	}
}

void common_1c14() {
	if (extended_play_frames_remaining>0) {
		if (extended_play_frames_remaining&16) {
			extended_play_visible=1;
			write_hud_message(297,(char *)"EXTENDED PLAY!",0x22);
		} else {
			extended_play_visible=0;
			clear_hud_characters(297,14);
		}
		extended_play_frames_remaining--;
	}
}
