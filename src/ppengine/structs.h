#ifndef __STRUCTS_H
#define __STRUCTS_H

#define HUD_CHARACTER_WIDTH 32
#define HUD_CHARACTER_HEIGHT 28
#define HUD_CONTENT_LENGTH (HUD_CHARACTER_WIDTH*HUD_CHARACTER_HEIGHT)

#include <inttypes.h>

struct movingobject {
	uint16_t type_and_visibility;					// offset 0000
	uint32_t forward_position;			            // offset 0002
	int16_t sideways_position;                      // offset 0006
	int16_t player_forward_position_difference;	    // offset 0008
	int16_t player_sideways_position_difference;    // offset 000a
	uint16_t display_variant;                       // offset 000c
	int32_t current_speed;							// offset 000e
	uint16_t maximum_speed;                         // offset 0012
	uint16_t unknown_attribute;                     // offset 0014
	int16_t sideways_movement;                      // offset 001a
	int16_t one_time_speed_modification;			// offset 001c
	int16_t explosion_countdown;                    // offset 001e	
};

struct sceneryobject {
	uint16_t forward_position;                      // offset 0002
	int16_t sideways_position;                      // offset 0002
	int16_t player_forward_position_difference;     // offset 0004
	int16_t player_sideways_position_difference;    // offset 0006
    uint32_t scenery_appearance;
};

struct hudentry {
	uint8_t character;
	uint8_t attribute;
};

#endif
