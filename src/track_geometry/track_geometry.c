#include <stdio.h>
#include <inttypes.h>
#include "track_geometry/track_geometry.h"
#include "track_geometry/points.h"
#include "track_geometry/subpoints.h"
#include <stdlib.h>

#define M_PI 3.14159265358979323846

int track_geometry_initialise(int8_t *track_curve_data) {
	if (!allocate_points()) {
		printf("Failed to allocate memory for track points. Exiting.\n");
		return 0;
	}
	derive_points_from_track_curve_data(track_curve_data);

	if (!allocate_subpoints()) {
		printf("Failed to allocate memory for track subpoints. Exiting.\n");
		return 0;
	}
	derive_subpoints_from_points(get_points());
	free_points();

	if (!allocate_segments()) {
		printf("Failed to allocate memory for track segments. Exiting.\n");
		return 0;
	}
	derive_segments_from_subpoints(get_subpoints());
	return 1;
}

struct segment *track_geometry_get_segments() {
	return get_segments();
}

struct vertex2d *track_geometry_get_subpoints() {
	return get_subpoints();	
}

struct vertex2d track_geometry_get_object_world_coordinates(uint32_t forward_position, int16_t sideways_position) {
	struct vertex2d world_coordinates;
	struct vertex2d current_segment_sideways_position;
	struct vertex2d next_segment_sideways_position;
	struct segment *object_current_segment;
	struct segment *object_next_segment;
	struct segment *segments=get_segments();

	object_current_segment=&segments[(forward_position>>16)];
	object_next_segment=&segments[((forward_position>>16)+1)&65535];

	vertex2d_interpolate(&current_segment_sideways_position,&object_current_segment->centre,&object_current_segment->track_right_edge,sideways_position,1800);
	vertex2d_interpolate(&next_segment_sideways_position,&object_next_segment->centre,&object_next_segment->track_right_edge,sideways_position,1800);
	vertex2d_interpolate(&world_coordinates,&current_segment_sideways_position,&next_segment_sideways_position,forward_position&65535,65536);

	return world_coordinates;
}

double track_geometry_get_object_natural_rotation_radians(uint32_t forward_position) {
	double current_segment_angle;
	double next_segment_angle;
	struct segment *segments;

	segments=get_segments();
	current_segment_angle=segments[(forward_position>>16)].angle_radians;
	next_segment_angle=segments[((forward_position>>16)+1)&65535].angle_radians;
	if (abs(next_segment_angle-current_segment_angle)>(M_PI)) {
		if (next_segment_angle<current_segment_angle) {
			next_segment_angle+=M_PI*2;
		} else {
			current_segment_angle+=M_PI*2;
		}
	}
	return current_segment_angle+((next_segment_angle-current_segment_angle)*(forward_position&65535)/65536);
}


void track_geometry_terminate() {
	free_segments();
	free_subpoints();
}

