#include "ppengine/sub/common/7b6.h"
#include "ppengine/engine.h"

void common_7b6() {
	if (ticks_remaining>0xc8) {
		return;
	} else if (ticks_remaining==0xc8) {
		// loc_7ee
		unknown_8022=0x4;
		unknown_8020=0x73;
	} else if (ticks_remaining>0xb4) {
		// loc_7fc
		if ((unknown_8030&1)==0) {
			return;
		}
		unknown_8020=0;
	} else if (ticks_remaining==0xb4) {
		unknown_8020=0;
		// TODO: do we need to implement instructions at 7ce-7d6?
		function_number_seconds_bcd=0;
		unknown_8022=0x5;
		unknown_8020=0x73;
	}
}


