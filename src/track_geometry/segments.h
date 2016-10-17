#ifndef __TRACK_GEOMETRY_SEGMENTS_H
#define __TRACK_GEOMETRY_SEGMENTS_H

#define NUMBER_OF_SEGMENTS 65536

#include "geometry/vertex2d.h"

struct segment {
	struct vertex2d centre;
	struct vertex2d track_left_edge;
	struct vertex2d track_right_edge;
	double angle_radians;
};

int allocate_segments();
struct segment *get_segments();
void derive_segments_from_subpoints(struct vertex2d *subpoints);
void free_segments();

#endif
