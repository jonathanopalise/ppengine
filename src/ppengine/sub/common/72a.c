#include "ppengine/sub/common/72a.h"
#include "ppengine/sub/common/7b6.h"
#include "ppengine/sub/common/a6a.h"
#include "ppengine/engine.h"
#include "ppengine/sub2/functionqueue.h"

void common_72a() {
	if ((ticks_remaining&3)==0) {
		queue_sub2_function(((ticks_remaining>>2)&7)+8);
	}

	// loc_75e
	common_7b6();
	if (ticks_remaining>0) {
		// loc_770
		ticks_remaining--;
		if (ticks_remaining==0) {
			jump_table_subfunction_number++;
			unknown_8020=0;
			previous_lap_time_display_ticks_remaining=0;
			session_end_animation_ticks_remaining=0;
			if (!waiting_for_coin) {
				queue_sub2_function(0x18);
				unknown_82c2=1;
			}
			common_a6a();
		}
	} else {
		ticks_remaining=0xdc;
	}
}


