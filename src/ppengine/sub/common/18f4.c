#include <inttypes.h>
#include "ppengine/sub/common/18f4.h"
#include "ppengine/sub/lib/bcd.h"

uint32_t common_18f4(uint32_t bcd_number_1, uint32_t bcd_number_2) {
	/*uint32_t result;
	uint32_t native_number_1;
	uint32_t native_number_2;
	uint32_t added_natives;

	native_number_1=bcd_to_native(bcd_number_1);
	native_number_2=bcd_to_native(bcd_number_2);
	added_natives=native_number_1+native_number_2;
	result=native_to_bcd(added_natives);*/

	// http://homepage.cs.uiowa.edu/~jones/bcd/bcd.html
	uint32_t t1,t2,t3,t4,t5,t6;
    t1 = bcd_number_1 + 0x06666666;
    t2 = t1 + bcd_number_2;
    t3 = t1 ^ bcd_number_2;
    t4 = t2 ^ t3;
    t5 = ~t4 & 0x11111110;
    t6 = (t5 >> 2) | (t5 >> 3);
    return t2 - t6;

	//return result;
}


