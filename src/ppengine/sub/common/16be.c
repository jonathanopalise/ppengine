#include "ppengine/sub/common/16be.h"
#include "ppengine/sub/common/1ad8.h"
#include "ppengine/engine.h"

void common_16be() {
	if (new_lap_just_started) {
		lap_completion_events_counted++;
		//printf("16be: lap_completion_events_counted++ (new value %d)\n",lap_completion_events_counted);
		if (player_has_passed_start_line_in_current_session==0) {
			// loc_1700
			player_has_passed_start_line_in_current_session=1;
		} else {
			if (player_has_passed_start_line_in_current_session==1) {
				previous_lap_time_bcd=current_lap_time_bcd;
				//printf("16be: previous_lap_time_bcd set to %x\n",previous_lap_time_bcd);
				common_1ad8();
				previous_lap_time_display_ticks_remaining=600;
				if (previous_lap_time_bcd<fastest_session_lap_bcd) {
					fastest_session_lap_bcd=previous_lap_time_bcd;
					if (previous_lap_time_bcd<fastest_ever_lap_bcd) {
						fastest_ever_lap_bcd=previous_lap_time_bcd;
					}
				}
			}
		}
	}
}


