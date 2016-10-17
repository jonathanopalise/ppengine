#include <stdio.h>
#include "ppengine/lib/hud.h"
#include "ppengine/engine.h"

void write_hud_message(int offset,char *message,uint8_t attribute) {
	char *current_character_source;
	char current_character;
	struct hudentry *current_character_destination;

	current_character_destination=&hud_content[offset];
	current_character_source=message;
	current_character=*current_character_source;
	while (current_character!=0) {
		current_character_destination->character=current_character;
		current_character_destination->attribute=attribute;
		current_character_source++;
		current_character_destination++;
		current_character=*current_character_source;
	}
}

void write_hud_bcd_16(int offset,uint16_t bcd,uint8_t attribute) {
	char buffer[2] = {0};
	int clear_leading_zero;

	clear_leading_zero=1;
	if (((bcd>>8)&0xf)==0) {
		*buffer=' ';
	} else {
		*buffer=((bcd>>8)&0xf)+48;
		clear_leading_zero=0;
	}
	write_hud_message(offset,buffer,attribute);
	if ((((bcd>>4)&0xf)==0) && clear_leading_zero) {
		*buffer=' ';
	} else {
		*buffer=((bcd>>4)&0xf)+48;
	}
	write_hud_message(offset+1,buffer,attribute);
	*buffer=(bcd&0xf)+48;
	write_hud_message(offset+2,buffer,attribute);
}

void clear_hud_characters(int offset,int count) {
	struct hudentry *current_character_destination;

	current_character_destination=&hud_content[offset];
	while (count>0) {
		current_character_destination->character=' ';
		current_character_destination++;
		count--;
	}
}
