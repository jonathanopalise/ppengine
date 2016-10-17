#ifndef __SCENE_OSG_SCENE_H
#define __SCENE_OSG_SCENE_H

#include "scene/moving_object_model_type.h"
#include "scene/gantry_appearance_type.h"
#include <osgGA/GUIEventHandler>

#define DISPLAY_CHANNEL_TITLE_SCREEN 1
#define DISPLAY_CHANNEL_IN_GAME 2

void osg_scene_open();
void osg_scene_add_gantry(double world_coordinates_x,double world_coordinates_y,double rotation_radians);
void osg_scene_set_gantry_light_illumination(int light_index, int illuminated);
void osg_scene_set_gantry_texture(int texture_index);
void osg_scene_add_scenery_object(double world_coordinates_x,double world_coordinates_y,double rotation_radians,int model_index);
void osg_scene_set_moving_object_attributes(int object_index,double world_coordinates_x,double world_coordinates_y,double rotation_radians,int moving_object_model,int visible);
void osg_scene_start_car_explosion(int object_index);
void osg_scene_end_car_explosion(int object_index);
void osg_scene_set_camera_position(double camera_x, double camera_y, double object_x, double object_y);
void osg_scene_close();
void osg_scene_generate_frame();
void osg_scene_register_event_handler(osg::ref_ptr<osgGA::GUIEventHandler> eventHandler);
void osg_scene_update_hud_character(int hud_x,int hud_y,uint8_t character,uint8_t attribute);
void osg_scene_set_display_channel(int display_channel);
void osg_scene_set_game_over_visibility(int visible);
int osg_scene_active();

#endif

