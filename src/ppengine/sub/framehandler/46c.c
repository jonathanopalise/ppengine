#include "ppengine/sub/framehandler/46c.h"
#include "ppengine/engine.h"
#include "ppengine/sub/common/a2e.h"
#include "ppengine/sub2/functionqueue.h"
#include "ppengine/sub/detectinsertedcoin.h"

void frame_handler_46c() {
	DETECT_INSERTED_COIN
	qualifying_position_minus_one=0x7;
	common_a2e();
	queue_sub2_function(0x0);
	queue_sub2_function(0x16);
	queue_sub2_function(0x6);
}

