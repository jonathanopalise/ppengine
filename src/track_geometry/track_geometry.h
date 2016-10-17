#ifndef __TRACK_GEOMETRY_TRACK_GEOMETRY_H
#define __TRACK_GEOMETRY_TRACK_GEOMETRY_H

#include <inttypes.h>
#include "track_geometry/segments.h"
#include "geometry/vertex2d.h"

int track_geometry_initialise(int8_t *track_curve_data);
struct segment *track_geometry_get_segments();
struct vertex2d *track_geometry_get_subpoints();
struct vertex2d track_geometry_get_object_world_coordinates(uint32_t forward_position, int16_t sideways_position);
double track_geometry_get_object_natural_rotation_radians(uint32_t forward_position);
void track_geometry_terminate();

#endif
