#include "ppengine/sub/common/17da.h"
#include "ppengine/sub/common/1844.h"
#include "ppengine/sub/lib/bcd.h"
#include "ppengine/lib/hud.h"
#include "ppengine/engine.h"
#include <inttypes.h>

static const uint8_t display_speed_multiply_lookup[] = {0x14,0x14,0x17,0x19};

void common_17da() {
	uint16_t current_speed_bcd;
	uint16_t displayed_speed;
	int show_speed=1;

	current_speed_bcd=native_to_bcd(((current_speed_8_bit_candidate_3>>12)*display_speed_multiply_lookup[race_initial_timer_switch_2&6])>>8);
	if (current_speed_bcd>session_top_speed_bcd) {
		session_top_speed_bcd=current_speed_bcd;
	}

	show_speed=1;
	if (waiting_for_coin) {
		// loc_1828
		displayed_speed=displayed_speed_outside_gameplay;
	} else {
		if (session_end_animation_ticks_remaining==0) {
			displayed_speed=current_speed_bcd;
		} else {
			session_end_animation_ticks_remaining--;
			displayed_speed=session_top_speed_bcd;
			if ((session_end_animation_ticks_remaining&0x1f)>18) {
				show_speed=0;
			}
		}
	}
	if (show_speed) {
		write_hud_message(116,(char *)"SPEED",1);
		write_hud_bcd_16(122,displayed_speed,1);
		write_hud_message(125,(char *)"km",1);
	} else {
		clear_hud_characters(116,11);
	}

	common_1844();
}


