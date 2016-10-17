#include "ppengine/engine.h"

void update_pseudorandom_number() {
	uint16_t r0;
	r0=pseudorandom_number;
	r0+=r0;
	r0+=r0;
	r0+=pseudorandom_number;
	r0+=1;
	r0+=frame_counter;
	pseudorandom_number=r0;
}


