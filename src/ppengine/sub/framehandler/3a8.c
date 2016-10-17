#include "ppengine/sub/framehandler/3a8.h"
#include "ppengine/engine.h"

void frame_handler_3a8() {
	if (ticks_remaining>0) {
		ticks_remaining--;
		if (ticks_remaining==0) {
			jump_table_subfunction_number++;
		}
	} else {
		ticks_remaining=0x1e;
	}
}

