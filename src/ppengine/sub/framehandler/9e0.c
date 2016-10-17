#include "ppengine/sub/framehandler/9e0.h"
#include "ppengine/sub/common/bc6.h"
#include "ppengine/sub/lib/bcd.h"
#include "ppengine/lib/hud.h"
#include "ppengine/engine.h"
#include <inttypes.h>

void common_1eae();

void frame_handler_9e0() {
    common_bc6();
    common_1eae();
    current_lap_time_bcd=0;
    unknown_80e8=0;
    engine_sound_pitch=0;

    if (qualifying_bonus==0) {
        if (ticks_remaining!=0) {
            // loc_a0c
            ticks_remaining--;
            if (ticks_remaining==0) {
                jump_table_subfunction_number++;
                qualifying_engine_started=0;
                previous_lap_time_display_ticks_remaining=0;
                session_end_animation_ticks_remaining=0;
                clear_hud_characters(648,150);
            }
        } else {
            ticks_remaining=40;
        }
    }
    
}

void common_1eae() {
    uint16_t lap_time_attribute;
    uint16_t qualifying_position_attribute;
    uint16_t bonus_attribute;
    char buffer[2] = {0};
    int current_qualifying_position;
    uint8_t letter_colour;
    int hud_offset;

    if (qualifying_outcome_cycling_value_tracker==0) {
        // loc_1fb2
        frames_until_next_countdown_update--;
        if (frames_until_next_countdown_update==0) {
            frames_until_next_countdown_update=8;
            if (qualifying_bonus>0) {
                qualifying_bonus=native_to_bcd(bcd_to_native(qualifying_bonus)-20);
                current_score_times_100_bcd=native_to_bcd(bcd_to_native(current_score_times_100_bcd)+0x20000);
                sample_player_2|=0x80;
            }
        }
        // loc_1ec8
        lap_time_attribute=1;
        qualifying_position_attribute=0x23;
        bonus_attribute=(current_cycling_colour&0xf)+0x20;
    } else {
        qualifying_outcome_cycling_value_tracker--;
        if (qualifying_outcome_cycling_value_tracker>=150) {
            // loc_1ede
            lap_time_attribute=(current_cycling_colour&0xf)+0x20;
            qualifying_position_attribute=1;
            bonus_attribute=1;
        } else if (qualifying_outcome_cycling_value_tracker>=60) {
            // loc_1ef4
            lap_time_attribute=1;
            qualifying_position_attribute=(current_cycling_colour&0xf)+0x20;
            bonus_attribute=1;
        } else {
            // loc_1ec8
            lap_time_attribute=1;
            qualifying_position_attribute=0x23;
            bonus_attribute=(current_cycling_colour&0xf)+0x20;
        }
    }

    // loc_1f08
	write_hud_message(649,(char *)"LAP TIME   \"",lap_time_attribute);
	*buffer=(previous_lap_time_bcd>>12)+48;
	write_hud_message(658,buffer,lap_time_attribute);
	*buffer=((previous_lap_time_bcd>>8)&0xf)+48;
	write_hud_message(659,buffer,lap_time_attribute);
	*buffer=((previous_lap_time_bcd>>4)&0xf)+48;
	write_hud_message(661,buffer,lap_time_attribute);
	*buffer=(previous_lap_time_bcd&0xf)+48;
	write_hud_message(662,buffer,lap_time_attribute);

    if (qualifying_position_minus_one==0) {
        // loc_1f7c
        write_hud_message(713,(char *)"POLE POSITION!",qualifying_position_attribute);
    } else {
        write_hud_message(708,(char *)"POSITION",qualifying_position_attribute);
        current_qualifying_position=1;
        hud_offset=717;
        while (current_qualifying_position<=8) {
            if (current_qualifying_position==(qualifying_position_minus_one+1)) {
                letter_colour=qualifying_position_attribute;
            } else {
                letter_colour=1;
            }
			*buffer=current_qualifying_position+48;
            write_hud_message(hud_offset,buffer,letter_colour);
            current_qualifying_position++;
            hud_offset+=2;
        }
    }

    // loc_1f94
    write_hud_message(780,(char *)"BONUS",bonus_attribute);
    write_hud_bcd_16(786,qualifying_bonus,bonus_attribute);
    write_hud_message(789,(char *)"0",bonus_attribute);
}

