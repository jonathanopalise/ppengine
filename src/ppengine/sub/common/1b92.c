#include "ppengine/sub/common/1b92.h"
#include "ppengine/engine.h"

void common_1b92() {
	if ((moving_objects[PLAYER_CAR_OBJECT_INDEX].type_and_visibility&0xff)==4) {
		car_slowdown_factor=0xfed4;
	}
}


