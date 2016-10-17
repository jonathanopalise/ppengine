#include <stdio.h>
#include "ppengine/engine.h"
#include "ppengine/sub2/framehandler.h"
#include "ppengine/sub2/perframefunctions/playercarmovement.h"
#include "ppengine/sub2/perframefunctions/cpucarmovement.h"
#include "ppengine/sub2/perframefunctions/cpucarspawning.h"
#include "ppengine/sub2/perframefunctions/cpucarai.h"
#include "ppengine/sub2/perframefunctions/cpucarhiding.h"
#include "ppengine/sub2/perframefunctions/carcollisions.h"
#include "ppengine/sub2/perframefunctions/scenerycollisions.h"
#include "ppengine/sub2/perframefunctions/puddlecollisions.h"
#include "ppengine/sub2/perframefunctions/carexplosions.h"

void sub2_frame_handler_dispatch() {
	update_player_car_sideways_position_and_appearance();
	update_cpu_car_positions();
	spawn_new_cpu_cars();
	run_cpu_car_ai();
	hide_out_of_sight_cpu_cars();
	check_car_collisions();
	check_scenery_collisions();
	check_puddle_collisions();
	update_car_explosions();
	frame_counter++;
}


