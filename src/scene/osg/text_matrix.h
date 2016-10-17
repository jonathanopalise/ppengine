#ifndef __SCENE_OSG_TEXT_MATRIX_H
#define __SCENE_OSG_TEXT_MATRIX_H

#include <osg/Geode>
#include <osgText/Text>

osg::ref_ptr<osg::Geode> osg_text_matrix_create_geode();
void osg_text_matrix_set_character_and_attribute(int character_x, int character_y, char character, int attribute);

#endif

