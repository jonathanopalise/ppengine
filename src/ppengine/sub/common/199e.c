#include "ppengine/sub/common/199e.h"
#include "ppengine/sub/common/353a.h"
#include "ppengine/engine.h"

void common_199e() {
	if (qualifying_session_state==1) {
		race_hundredths_elapsed++;
		if (race_hundredths_elapsed>=10) {
			race_hundredths_elapsed=0;
		}
		unknown_a852--;
		if (unknown_a852==0) {
			unknown_a852=4;
			race_tenths_elapsed++;
			if (race_tenths_elapsed>=10) {
				race_tenths_elapsed=0;
				race_seconds_elapsed++;
			}
		}
		race_time_elapsed_bcd=(race_hundredths_elapsed&0xf)|((race_tenths_elapsed&0xf)<<4)|((common_353a(race_seconds_elapsed)<<8)&0xfffff);
	}
}


