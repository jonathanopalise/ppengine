#include <inttypes.h>
#include "ppengine/sub/common/1928.h"
#include "ppengine/sub/common/1ad2.h"
#include "ppengine/engine.h"

void common_1928() {
	if (player_has_passed_start_line_in_current_session==-1) {
		// loc_1ad2
		common_1ad2();
	} else if (player_has_passed_start_line_in_current_session==1) {
		lap_time_hundredths++;
		if (lap_time_hundredths>=10) {
			lap_time_hundredths=0;
		}

		// loc_194c
		ticks_until_next_lap_time_tenths_change--;
		if (ticks_until_next_lap_time_tenths_change==0) {
			ticks_until_next_lap_time_tenths_change=4;
			lap_time_tenths++;
			if (lap_time_tenths>=10) {
				lap_time_tenths=0;
				lap_time_seconds++;
			}
		}

		// loc_196e
		current_lap_time_bcd=(((lap_time_seconds/10))<<12)|((lap_time_seconds%10)<<8)|(lap_time_tenths<<4)|lap_time_hundredths;
	}

}


