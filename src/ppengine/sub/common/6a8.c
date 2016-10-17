#include "ppengine/sub/common/6a8.h"
#include "ppengine/engine.h"
#include "ppengine/sub/common/1ad2.h"

uint8_t qualifying_initial_seconds_remaining_lookup[4]={ 0x5a, 0x64, 0x6e, 0x78};

void common_6a8() {
	engine_sound_active=0;
	full_race_distance_completed=0;
	unknown_828c=0;
	unknown_8290=0x120000;
	unknown_8292=0;
	cars_passing_tracking_enabled=0;
	current_score=0;
	unknown_82a6=0;
	cpu_car_spawning_mode=1;
	session_seconds_updates_enabled=1;
	frames_until_next_countdown_update=0xa;
	scoring_enabled_flag=0;
	lap_completion_events_counted=0;
	//printf("6a8: setting lap_completion_events_counted=0\n");
	number_of_cpu_cars_in_use=3;

	// call set_qualifying_initial_seconds_remaining
	// TODO: separate functionality out into common_1a8c function within this file
	second_fractions_remaining=0x28;
	seconds_remaining=qualifying_initial_seconds_remaining_lookup[qualifying_initial_timer_switch&3];
	common_1ad2();

	lap_completion_events_in_single_game=(race_initial_timer_switch_1&1)+6;
	//printf("6a8: setting lap_completion_events_in_single_game=%d\n",lap_completion_events_in_single_game);
	jump_table_subfunction_number++;

}

