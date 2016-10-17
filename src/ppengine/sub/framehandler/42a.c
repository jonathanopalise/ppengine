#include "ppengine/sub/framehandler/42a.h"
#include "ppengine/sub/detectinsertedcoin.h"
#include "ppengine/engine.h"
#include "ppengine/sub/common/6a8.h"
#include "ppengine/sub2/functionqueue.h"

void frame_handler_42a() {
	DETECT_INSERTED_COIN
	waiting_for_coin=1;
	queue_sub2_function(0x5);
	common_6a8();
}

