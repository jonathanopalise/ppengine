#ifndef __TRACK_GEOMETRY_POINTS_H
#define __TRACK_GEOMETRY_POINTS_H

int allocate_points();
struct vertex2d *get_points();
void derive_points_from_track_curve_data(int8_t *track_curve_data);
void free_points();

#endif
