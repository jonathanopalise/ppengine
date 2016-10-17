#include "ppengine/sub2/perframefunctions/playercarmovement.h"
#include "ppengine/engine.h"

void update_player_car_sideways_position_and_appearance() {
	moving_objects[PLAYER_CAR_OBJECT_INDEX].sideways_position=((-high_precision_sideways_position)>>4)+((-high_precision_sideways_position>>6));
	moving_objects[PLAYER_CAR_OBJECT_INDEX].display_variant=((((forward_position>>16)>>3)&1)<<8)|(steering_or_car_orientation&0xff);
}

