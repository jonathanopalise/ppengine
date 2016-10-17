#include "ppengine/sub/framehandler/c34.h"
#include "ppengine/sub/common/bc8.h"
#include "ppengine/sub/common/1310.h"
#include "ppengine/lib/hud.h"
#include "ppengine/engine.h"

void frame_handler_c34() {
	common_bc8();
	common_1310();

	if (ticks_remaining>0) {
		// loc_c46
		ticks_remaining--;
		if (ticks_remaining==0) {
			jump_table_subfunction_number++;
			qualifying_session_state=0;
			time_bonus=seconds_remaining;
			clear_hud_characters(709,24);
		}
	} else {
		ticks_remaining=30;
	}
}

