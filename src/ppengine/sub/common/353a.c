#include <inttypes.h>

uint32_t common_353a(uint16_t native_number) {
	uint32_t result;
	int index;

	result=0;
	for (index=0; index<5; index++) {
		result|=(native_number%10)<<28;
		result>>=4;
		native_number/=10;
	}
	result>>=8;
	return result;
}

