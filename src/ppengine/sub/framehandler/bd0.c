#include <stdlib.h>
#include "ppengine/sub/framehandler/bd0.h"
#include "ppengine/sub/common/1ff0.h"
#include "ppengine/sub/common/1906.h"
#include "ppengine/sub/common/1928.h"
#include "ppengine/sub/common/199e.h"
#include "ppengine/sub/common/bc6.h"
#include "ppengine/sub/common/165a.h"
#include "ppengine/sub/common/16be.h"
#include "ppengine/sub/common/1310.h"
#include "ppengine/sub/common/1b92.h"
#include "ppengine/sub/common/1786.h"
#include "ppengine/sub/common/1ba4.h"
#include "ppengine/sub2/functionqueue.h"
#include "ppengine/engine.h"

void common_150e();
void common_15de();
void common_1bc8();
void common_1bf8();

void frame_handler_bd0() {
	//printf("calling frame handler bd0 (player_car_stopped_at_session_end=%d)\n",player_car_stopped_at_session_end);

	internal_accel_pedal=4;
	internal_brake_pedal=0;
	common_150e(); // see below
	common_15de(); // see below
	common_1ff0(); // player car physics
	common_1906(); // update seconds_remaining
	common_1928(); // update current_lap_time_bcd
	common_199e(); // update race_time_elapsed_bcd
	common_bc6(); // update hud speed, seconds, laptime values
	common_1bc8(); // see below
	common_165a(); // check qualifying elbigibility
	common_16be(); // track lap times and lap count
	common_1310(); // write "YOUR RECORD (sec/msec) to hud if applicable
	if (player_car_stopped_at_session_end) {
		jump_table_subfunction_number++;
		current_race_lap++;
		player_has_passed_start_line_in_current_session=0;
		//printf("bd0: previous_lap_time_bcd set to %x\n",previous_lap_time_bcd);
		previous_lap_time_bcd=fastest_session_lap_bcd;
		current_lap_time_bcd=fastest_session_lap_bcd;
		lap_time_bcd_displayed_outside_gameplay=fastest_session_lap_bcd;
		previous_lap_time_display_ticks_remaining=600;
		displayed_speed_outside_gameplay=session_top_speed;
		session_end_animation_ticks_remaining=600;
		unknown_828c=0;
		unknown_80e8=0;
		engine_sound_pitch=0;
	}
}

void common_150e() {
	// inputs: current_speed_8_bit_candidate_3, car_slowdown_factor, unknown_81be, unknown_828c
	// outputs: unknown_828c, current_speed_8_bit_candidate_3, unknown_81be, car_slowdown_factor

	uint32_t unknown_828c_temp_unsigned;
	int32_t unknown_828c_temp_signed;

	//printf("150e: current_speed_8_bit_candidate_3 was %d\n",current_speed_8_bit_candidate_3);
	//printf("150e: unknown_81be is %d\n",unknown_81be);
	//printf("150e: speed adjustment value derived from unknon_81be is %d\n",((abs(unknown_81be)&0xffff)<<10));
	current_speed_8_bit_candidate_3-=((abs(unknown_81be)&0xffff)<<10);
	//printf("150e: current_speed_8_bit_candidate_3 is now %d\n",current_speed_8_bit_candidate_3);
	if (current_speed_8_bit_candidate_3<0) {
		//printf("150e: new value of current_speed_8_bit_candidate_3 is below 0 - normalising to 0\n");
		current_speed_8_bit_candidate_3=0;
	}
	if (car_slowdown_factor<0) {
		// loc_155a
		unknown_828c_temp_signed=car_slowdown_factor;
		unknown_828c_temp_signed=(unknown_828c_temp_signed<<10)+unknown_828c;
		if (unknown_828c_temp_signed<0) {
			unknown_828c_temp_signed=0;
		}
		unknown_828c=unknown_828c_temp_signed;
	} else {
		unknown_828c_temp_unsigned=unknown_828c+40000;
		if ((unknown_828c_temp_unsigned>>16)<250) {
			unknown_828c=unknown_828c_temp_unsigned;
		}
	}

	unknown_81be=0;
	car_slowdown_factor=0;
}

void common_15de() {
	//uint16_t unknown_8298_temp;
	uint16_t r0;
	uint16_t r1;

	// unknown_8290 appears to be a high precision player_forward_position_difference for player car
	// i.e. how far the player car appears from the camera

	forward_position+=(current_speed_8_bit>>3);
	display_road_vertical_scroll=forward_position>>16;
	//printf("15de: unknown_8290 was 0x%x\n",unknown_8290);
	//printf("15de: unknown_828c unprocessed is %d\n",unknown_828c);
	//printf("15de: addition value derived from unknown_828c is %d\n",unknown_828c>>3);
	unknown_8290+=(unknown_828c>>3);
	//printf("15de: unknown_8290 is now 0x%x\n",unknown_8290);
	moving_objects[PLAYER_CAR_OBJECT_INDEX].player_forward_position_difference=unknown_8290>>16;

	r0=unknown_8298;
	r1=((forward_position>>16)+(unknown_8290>>16));
	unknown_8298=r1;
	r1=~r1;
	if (((r0&r1)>>15)==1) {
		//printf("15de: set new_lap_just started to 1\n");
		new_lap_just_started=1;
		session_seconds_updates_enabled=0;
		sample_player_1|=32;
		engine_sound_active=0;
		queue_sub2_function(0x1b);
	} else {
		//printf("15de: set new_lap_just started to 0\n");
		new_lap_just_started=0;
	}
}

void common_1bc8() {
	int32_t unknown_8282_temp;

	common_1bf8();
	common_1b92(); // slow down player car if exploding (car_slowdown_factor=0xfed4)
	common_1786(); // change gantry appearance and show/hide checkered flag person if required
	common_1ba4(); // set full_race_distance_completed to 0 or 1

	// get top 16 bits of last recorded player speed
	// and normalise to 0-255 range
	unknown_8282_temp=(unknown_8282>>16);
	if (unknown_8282_temp<0) {
		unknown_8282_temp=0;
	} else if (unknown_8282_temp>0xff) {
		unknown_8282_temp=0xff;
	}

	// square normalised race end speed and divide by 256, write to unknown_81be
	unknown_81be=(((unknown_8282_temp*unknown_8282_temp)>>8)&0xff)+1;
}

void common_1bf8() {
	uint16_t r0;

	//printf("1bf8: unknown_8290 is 0x%x\n",unknown_8290);
	//printf("1bf8: forward_position>>16 is 0x%x\n",forward_position>>16);
	r0=(forward_position>>16)+(unknown_8290>>16);
	//printf("1bf8: r0 value is %x\n",r0);
	if ((r0>0xc00) && (r0<0x1000)) {
		player_car_stopped_at_session_end=1;
		//printf("1bf8: set player_car_stopped_at_session_end to 1\n");
	}
}
