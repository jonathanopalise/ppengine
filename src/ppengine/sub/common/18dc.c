#include "ppengine/sub/common/18dc.h"
#include "ppengine/sub/common/1c48.h"
#include "ppengine/sub/common/18c4.h"
#include "ppengine/engine.h"

void common_18dc() {
	uint32_t score_bcd;

	score_bcd=(current_score_times_100_bcd>>8)&0xfffffff0;
	common_1c48(102,score_bcd,2);
	score_bcd&=0xfffffff;
	common_18c4(score_bcd);
}


