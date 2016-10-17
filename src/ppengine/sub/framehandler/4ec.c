#include "ppengine/sub/framehandler/4ec.h"
#include "ppengine/sub/common/148e.h"
#include "ppengine/sub/common/1572.h"
#include "ppengine/sub/common/1ff0.h"
#include "ppengine/sub/common/1906.h"
#include "ppengine/sub/common/1844.h"
#include "ppengine/sub/common/1b2e.h"
#include "ppengine/sub/common/165a.h"
#include "ppengine/sub/common/16be.h"
#include "ppengine/sub/detectinsertedcoin.h"
#include "ppengine/engine.h"

void frame_handler_4ec() {
	DETECT_INSERTED_COIN

	// sub_145e
	internal_accel_pedal=7;
	internal_brake_pedal=0;

	common_148e();
	common_1572();
	common_1ff0();
	common_1906();
	common_1844();
	common_1b2e();
	common_165a();
	common_16be();

	if (ticks_remaining>0) {
		ticks_remaining--;
		if (ticks_remaining==0) {
			//jump_table_subfunction_number++;
			jump_table_function_number=1;
			jump_table_subfunction_number=1;
			engine_sound_active=0;
		}
	} else {
		ticks_remaining=0x708;
		demo_frames=0;
	}
}

