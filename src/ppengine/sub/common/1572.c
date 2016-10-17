#include <inttypes.h>
#include "ppengine/sub/common/1572.h"
#include "ppengine/sub/data/track_curve_data.h"
#include "ppengine/engine.h"

void common_1572() {
	// most significant data element accessed at lowest address

	// with rr1:
	// r0 contains most significant bits
	// r1 contains least significant bits

	uint32_t old_forward_position;
	uint16_t forward_position_msw_temp;

	old_forward_position=forward_position;
	forward_position_msw_temp=forward_position>>16;
	forward_position+=current_speed_8_bit_candidate_3>>3;
	display_road_vertical_scroll=forward_position>>16;
	if (old_forward_position>forward_position) {
		new_lap_just_started=1;
	} else {
		new_lap_just_started=0;
	}

	// loc_1598
	safe_to_change_gantry_appearance=0;
	if (((display_road_vertical_scroll-0xc000)>display_road_vertical_scroll) ||
        ((forward_position_msw_temp-0xc000)<forward_position_msw_temp)) {
		safe_to_change_gantry_appearance=0;
	} else {
		safe_to_change_gantry_appearance=1;
	}

	// loc_15b0
	curve_at_player_forward_position=(int16_t)(track_curve_data[forward_position>>24]);
	background_position+=(int32_t)(((current_speed_8_bit_candidate_3>>16)<<8)>>2)*(int32_t)(-curve_at_player_forward_position);	
	display_background_horizontal_scroll=background_position>>16;
}


