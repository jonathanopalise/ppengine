#include <stdio.h>
#include "client.h"
extern "C" {
#include "engine.h"
}
#include "scene/scene.h"
#include "input/input.h"
#include "track_geometry/track_geometry.h"
#include "audio/audio.h"
#include "sub/data/track_curve_data.h"

int main(void) {
	engine_initialise();
	engine_register_sound_effect_callback(audio_play_effect);
	track_geometry_initialise(track_curve_data);
	scene_open(scenery_objects);
	input_initialise();
	audio_open();
	while (scene_active()) {
		update_engine_state_from_input();
		engine_execute_frame();
		scene_update_display_mode_from_game_state(jump_table_function_number,jump_table_subfunction_number);
		scene_update_moving_objects_and_camera(moving_objects,forward_position,clipped_steering);
		scene_update_hud_content(hud_content);
		scene_update_gantry(gantry_and_starting_lights_appearance);
		audio_update(moving_objects,engine_sound_pitch,engine_sound_active,skidding_volume);
		scene_generate_frame();
	}
	audio_close();
	scene_close();
	track_geometry_terminate();

	return 0;

}

