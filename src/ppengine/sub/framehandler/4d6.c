#include "ppengine/sub/framehandler/4d6.h"
#include "ppengine/sub/common/aba.h"
#include "ppengine/sub/common/1c48.h"
#include "ppengine/engine.h"
#include "ppengine/sub/detectinsertedcoin.h"

void frame_handler_4d6() {
	DETECT_INSERTED_COIN
	common_1c48(38,high_score_bcd,0x2d);
	common_aba();
}

