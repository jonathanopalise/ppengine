#include "ppengine/sub/common/1a26.h"
#include "ppengine/lib/hud.h"
#include "ppengine/engine.h"
#include <inttypes.h>

void common_1a26() {
	uint32_t display_value;
	int write_display_value;
	char buffer[2] = {0};

	write_display_value=1;
	if (waiting_for_coin) {
		// loc_1a3c
		display_value=lap_time_bcd_displayed_outside_gameplay;
	} else if (previous_lap_time_display_ticks_remaining>0) {
		// loc_1a42
		previous_lap_time_display_ticks_remaining--;
		if ((previous_lap_time_display_ticks_remaining&31)==0) {
			// loc_1a80
			clear_hud_characters(54,10);
			write_display_value=0;
		} else if ((previous_lap_time_display_ticks_remaining&31)==20) {
			display_value=previous_lap_time_bcd;
		} else {
			write_display_value=0;
		}
	} else {
		display_value=current_lap_time_bcd;
	}

	if (write_display_value) {
		// TODO: refactor this and the similar code in framehandler/9e0
		write_hud_message(54,(char *)"LAP   \"",4);
		if ((display_value>>12)>0) {
			*buffer=(display_value>>12)+48;
			//sprintf(buffer,"%c",(display_value>>12)+48);
		}
		write_hud_message(58,buffer,4);
		*buffer=((display_value>>8)&0xf)+48;
		//sprintf(buffer,"%c",((display_value>>8)&0xf)+48);
		write_hud_message(59,buffer,4);
		*buffer=((display_value>>4)&0xf)+48;
		//sprintf(buffer,"%c",((display_value>>4)&0xf)+48);
		write_hud_message(61,buffer,4);
		*buffer=(display_value&0xf)+48;
		//sprintf(buffer,"%c",(display_value&0xf)+48);
		write_hud_message(62,buffer,4);
	}
}


