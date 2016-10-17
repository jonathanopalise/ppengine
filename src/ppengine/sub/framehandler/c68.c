#include "ppengine/sub/framehandler/c68.h"
#include "ppengine/sub/common/bc8.h"
#include "ppengine/sub/common/12a2.h"
#include "ppengine/engine.h"

void frame_handler_c68() {
	common_bc8();
	common_12a2();

	if (ticks_remaining>0) {
		// loc_c7a
		ticks_remaining--;
		if (ticks_remaining==0) {
			jump_table_subfunction_number++;
		}
	} else {
		ticks_remaining=30;
	}
}

