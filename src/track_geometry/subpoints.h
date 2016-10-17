#ifndef __TRACK_GEOMETRY_SUBPOINTS_H
#define __TRACK_GEOMETRY_SUBPOINTS_H

#include "geometry/vertex2d.h"

int allocate_subpoints();
struct vertex2d *get_subpoints();
void derive_subpoints_from_points(struct vertex2d *points);
void free_subpoints();

#endif
