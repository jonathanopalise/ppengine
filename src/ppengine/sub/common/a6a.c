#include "ppengine/sub/common/a6a.h"
#include "ppengine/engine.h"

void common_a6a() {
	player_has_passed_start_line_in_current_session=0;
	previous_lap_time_bcd=0x19999;
	//printf("a6a: previous_lap_time_bcd set to %d\n",previous_lap_time_bcd);
	fastest_session_lap_bcd=0x19999;
	current_speed_8_bit_candidate_3=0;
	unknown_828c=0;
	high_precision_speed=0;
	session_engine_started=0;
	target_engine_revs=0;
	internal_accel_pedal=0;
	unknown_8222=0;
	clipped_steering_candidate_2=0;
	clipped_steering=0;
	background_position=0;
	seconds_into_session=0;
	session_top_speed=0;
	steering_wheel_rotation_candidate_2=steering_wheel_rotation;
}


