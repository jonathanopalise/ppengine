#include "ppengine/sub/common/1ba4.h"
#include "ppengine/engine.h"

void common_1ba4() {
	if (lap_completion_events_counted>lap_completion_events_in_single_game) {
		full_race_distance_completed=1;
	} else if (lap_completion_events_counted==lap_completion_events_in_single_game) {
		if (forward_position<0xfb400000) {
			full_race_distance_completed=0;
		} else {
			full_race_distance_completed=1;
		}
	}
}


