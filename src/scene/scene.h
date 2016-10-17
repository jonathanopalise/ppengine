#ifndef __SCENE_SCENE_H
#define __SCENE_SCENE_H

#include <inttypes.h>
#include "scene/moving_object_model_type.h"
#include "scene/gantry_appearance_type.h"
#include "engine.h"

void scene_open(struct sceneryobject *scenery_objects);
void scene_close();
void scene_generate_frame();
void scene_update_moving_objects_and_camera(struct movingobject *moving_objects, uint32_t player_forward_position, int16_t steering_or_car_orientation);
void scene_update_gantry(int gantry_and_starting_lights_appearance);
void scene_update_hud_content(struct hudentry *hud_content);
void scene_update_display_mode_from_game_state(int jump_table_function_number, int jump_table_subfunction_number);
int scene_active();

#endif

