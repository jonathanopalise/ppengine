#include "ppengine/sub/common/12a2.h"
#include "ppengine/lib/hud.h"
#include "ppengine/engine.h"

#define HIGHLIGHT_COLOUR 7

void write_2_digit_with_leading_zeroes(int offset, int value, int attribute);

void common_12a2() {

	uint16_t passing_bonus_attribute;
	uint16_t time_bonus_attribute;
	uint16_t temp;
	
	passing_bonus_attribute=HIGHLIGHT_COLOUR;
	time_bonus_attribute=1;
	if (cars_passed==0) {
		temp=passing_bonus_attribute;
		passing_bonus_attribute=time_bonus_attribute;
		time_bonus_attribute=temp;
	}
	write_hud_message(709,(char *)"PASSING BONUS  50x",passing_bonus_attribute);
	write_2_digit_with_leading_zeroes(727,cars_passed,passing_bonus_attribute);

	if (time_bonus>=0) {
		write_hud_message(776,(char *)"TIME BONUS 200x",time_bonus_attribute);
		write_2_digit_with_leading_zeroes(791,time_bonus,time_bonus_attribute);
	}
}

void write_2_digit_with_leading_zeroes(int offset, int value, int attribute) {
	char buffer[2] = {0};

	//sprintf(buffer,"%c",(value/10)+48);
	*buffer=(value/10)+48;
	write_hud_message(offset,buffer,attribute);
	*buffer=(value%10)+48;
	//sprintf(buffer,"%c",(value%10)+48);
	write_hud_message(offset+1,buffer,attribute);
}


