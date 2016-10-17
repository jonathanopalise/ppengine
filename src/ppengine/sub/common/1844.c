#include "ppengine/sub/common/1844.h"
#include "ppengine/engine.h"

void common_1844() {
	current_speed_8_bit=((((-high_precision_sideways_position)*curve_at_player_forward_position)>>7)*(current_speed_8_bit_candidate_3>>16))+current_speed_8_bit_candidate_3;
	if (current_speed_8_bit<0) {
		current_speed_8_bit&=0xffff;
	} else if (current_speed_8_bit>(0x118<<16)) {
		current_speed_8_bit=(current_speed_8_bit&0xffff)|(0x118<<16);
	}
}


