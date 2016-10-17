#include "ppengine/sub/lib/bcd.h"

uint32_t bcd_to_native(uint32_t bcd) {
	uint32_t current_multiplier;
	uint32_t result;

	current_multiplier=1;
	result=0;
	while (current_multiplier<=10000000) {
		result+=(bcd&15)*current_multiplier;
		bcd>>=4;
		current_multiplier*=10;
	}

	return result;
}

uint32_t native_to_bcd(uint32_t native) {
	uint32_t result;
	uint32_t current_divider;

	result=0;
	current_divider=1;
	while (current_divider<=10000000) {
		result>>=4;
		result|=(((native/current_divider)%10)<<28);
		current_divider*=10;
	}
	return result;
}

