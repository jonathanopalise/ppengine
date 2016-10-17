#include "ppengine/sub/common/1310.h"
#include "ppengine/engine.h"
#include "ppengine/lib/hud.h"
#include <stdio.h>

void common_1310() {
	char buffer[2] = {0};
	uint16_t attribute;

	if ((new_lap_just_started) || (qualifying_session_state==2)) {
		// loc_131e
		qualifying_session_state=2;
		attribute=current_cycling_colour+0x20;
		write_hud_message(709,(char *)"YOUR RECORD    \"   SEC",current_cycling_colour+0x20);
		*buffer=(race_time_elapsed_bcd>>16)+48;
		write_hud_message(721,buffer,attribute);
		*buffer=((race_time_elapsed_bcd>>12)&0xf)+48;
		write_hud_message(722,buffer,attribute);
		*buffer=((race_time_elapsed_bcd>>8)&0xf)+48;
		write_hud_message(723,buffer,attribute);
		*buffer=((race_time_elapsed_bcd>>4)&0xf)+48;
		write_hud_message(725,buffer,attribute);
		*buffer=(race_time_elapsed_bcd&0xf)+48;
		write_hud_message(726,buffer,attribute);
	}
}


