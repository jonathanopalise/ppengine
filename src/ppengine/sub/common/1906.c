#include "ppengine/sub/common/1906.h"
#include "ppengine/engine.h"

void common_1906() {
	if (session_seconds_updates_enabled) {
		second_fractions_remaining--;
		if (second_fractions_remaining==0) {
			second_fractions_remaining=40;
			seconds_into_session++;
			if (seconds_remaining!=0) {
				seconds_remaining--;
			}
		}
	}
}


