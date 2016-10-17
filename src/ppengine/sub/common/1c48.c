#include "ppengine/sub/common/1c48.h"
#include "ppengine/engine.h"

void common_1c48(int offset, uint32_t bcd ,uint8_t attribute) {
	struct hudentry *current_hud_entry;
	int characters_remaining=5;
	uint8_t character;

	offset-=5;
	uint32_t bcd_copy;
	bcd_copy=bcd<<12;
	character=bcd_copy>>28;
	while ((characters_remaining>1) && (character==0)) {
		bcd_copy<<=4;
		character=bcd_copy>>28;
		offset++;
		characters_remaining--;
	}

	offset+=characters_remaining;
	current_hud_entry=&hud_content[offset];
	current_hud_entry+=5;
	while (characters_remaining>0) {
		character=(bcd&0xf)+48;
		current_hud_entry->character=character;
		current_hud_entry->attribute=attribute;
		current_hud_entry--;
		characters_remaining--;
		bcd>>=4;
	}
	
}


