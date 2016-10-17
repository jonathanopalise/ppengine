#include "ppengine/sub/common/1786.h"
#include "ppengine/engine.h"
#include "ppengine/sub2/functionqueue.h"

void common_1786() {
	if (safe_to_change_gantry_appearance) {
		if ((lap_completion_events_counted==1) || (lap_completion_events_counted==4)) {
			// loc_17a4
			gantry_and_starting_lights_appearance=5;
		} else if (lap_completion_events_counted==lap_completion_events_in_single_game) {
			// loc_17ac
			gantry_and_starting_lights_appearance=6;
			queue_sub2_function(0x1a);
		}
	}
}


