#include "ppengine/sub/common/18c4.h"
#include "ppengine/sub/common/1c48.h"
#include "ppengine/engine.h"

void common_18c4(uint32_t score_bcd) {
	if (score_bcd>=high_score_bcd) {
		high_score_bcd=score_bcd;
	}
	common_1c48(38,high_score_bcd,5);
}

