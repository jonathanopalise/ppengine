#include "ppengine/sub/framehandler/808.h"
#include "ppengine/sub/common/bc6.h"
#include "ppengine/sub/common/840.h"
#include "ppengine/engine.h"
#include "ppengine/sub2/functionqueue.h"

void frame_handler_808() {
	common_bc6();
	if (ticks_remaining>0) {
		// loc_818
		ticks_remaining--;
		if (ticks_remaining==0) {
			jump_table_subfunction_number++;
			queue_sub2_function(3);
			common_840();
		}
	} else {
		ticks_remaining=0xb4;
	}
}

