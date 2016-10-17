#include "ppengine/sub/common/187e.h"
#include "ppengine/sub/common/18f4.h"
#include "ppengine/sub/common/353a.h"
#include "ppengine/sub/common/1c48.h"
#include "ppengine/sub/common/18c4.h"
#include "ppengine/engine.h"

void common_187e() {
	uint32_t amount_to_add_bcd;
	uint32_t source_current_score_bcd;
	uint32_t normalised_display_score_bcd;

	if (scoring_enabled_flag) {
		amount_to_add_bcd=common_353a(((current_speed_8_bit>>1)/0x4300)&0xffff);
	} else {
		amount_to_add_bcd=0;
	}

	// loc_189c
	current_score_times_100_bcd=common_18f4(current_score_times_100_bcd,amount_to_add_bcd);
	if (waiting_for_coin) {
		source_current_score_bcd=current_score_outside_gameplay_bcd;
	} else {
		source_current_score_bcd=current_score_times_100_bcd;
	}

	// loc_18b0
	normalised_display_score_bcd=(source_current_score_bcd>>8)&0xfffffff0;
	if (normalised_display_score_bcd>high_score_bcd) {
		high_score_bcd=normalised_display_score_bcd;
	}
	common_1c48(102,normalised_display_score_bcd,2);

	// loc_18c4
	common_18c4(normalised_display_score_bcd);
}



