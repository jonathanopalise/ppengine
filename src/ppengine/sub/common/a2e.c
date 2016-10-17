#include "ppengine/sub/common/a2e.h"
#include "ppengine/sub/common/840.h"
#include "ppengine/sub/common/1ad2.h"
#include "ppengine/sub/common/a6a.h"
#include "ppengine/engine.h"
#include "ppengine/sub2/functionqueue.h"
#include "ppengine/sub/data/race_seconds_lookup.h"

void common_1afe();
void common_1aa6();

void common_a2e() {
	queue_sub2_function(0x1);
	scoring_enabled_flag=0;
	number_of_cpu_cars_in_use=4;
	lap_completion_events_counted++;
	common_1afe();
	common_1aa6();
	jump_table_subfunction_number++;
	common_840();
	common_a6a();
}

void common_1afe() {
	qualifying_session_state=0;
	race_hundredths_elapsed=0;
	unknown_a852=4;
	race_tenths_elapsed=0;
	race_seconds_elapsed=0;
	race_time_elapsed_bcd=0;
	// no equivalent for instruction at 1b22 because
	// this is already done by line above
}

void common_1aa6() {
	second_fractions_remaining=0x28;
	seconds_remaining=race_seconds_lookup[(((race_initial_timer_switch_2&7)<<3)|((race_initial_timer_switch_1&1)<<6))>>1]&0x7f;
	common_1ad2();
}


