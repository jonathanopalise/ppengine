#include "ppengine/sub/common/1a0a.h"
#include "ppengine/lib/hud.h"
#include "ppengine/engine.h"
#include <inttypes.h>

void common_1a0a() {
	uint16_t seconds_remaining_output; 

	char buffer[2] = {0};
	int index;
	int offset;
	int digit;
	int show_zeroes;
	int divider;

	if (waiting_for_coin) {
		seconds_remaining_output=0;
	} else {
		seconds_remaining_output=seconds_remaining;
	}

	offset=110;
	show_zeroes=0;
	divider=100;
	for (index=0; index<3; index++) {
		digit=seconds_remaining_output/divider;
		divider/=10;
		digit%=10;
		if (digit==0) {
			if (show_zeroes || index==2) {
				digit=48;
			} else {
				digit=24;
			}
		} else {
			show_zeroes=1;
			digit+=48;
		}
		//sprintf(buffer,"%c",digit);
		*buffer=digit;
		write_hud_message(offset,buffer,3);
		offset++;
	}
}


