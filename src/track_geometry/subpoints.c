#include <math.h>
#include <stdlib.h>
#include "track_geometry/subpoints.h"

#define SUBPOINTS_PER_POINT 256.0

struct vertex2d *subpoints;

int allocate_subpoints() {
	subpoints=(struct vertex2d *) malloc(sizeof(struct vertex2d)*256*SUBPOINTS_PER_POINT);
	return subpoints!=0;
}

struct vertex2d *get_subpoints() {
	return subpoints;
}

void derive_subpoints_from_points(struct vertex2d *points) {
	struct vertex2d *current_point;
	struct vertex2d *next_point;
	struct vertex2d *previous_point;
	struct vertex2d *two_points_forward;
	struct vertex2d *current_subpoint;

	struct vertex2d bezier_source_1;
	struct vertex2d bezier_source_2;

	struct vertex2d bezier_p0;
	struct vertex2d bezier_p1;
	struct vertex2d bezier_p2;
	struct vertex2d bezier_p3;
	struct vertex2d bezier_p0_to_p1;
	struct vertex2d bezier_p1_to_p2;
	struct vertex2d bezier_p2_to_p3;
	struct vertex2d bezier_p0p1_to_p1p2;
	struct vertex2d bezier_p1p2_to_p2p3;

	int point_index;
	int subpoint_index;

	current_subpoint=subpoints;
	for (point_index=0; point_index<256; point_index++) {
		previous_point=&points[(point_index-1)&0xff];
		current_point=&points[point_index];
		next_point=&points[(point_index+1)&0xff];
		two_points_forward=&points[(point_index+2)&0xff];

		vertex2d_copy(&bezier_p0,current_point);
		vertex2d_copy(&bezier_p3,next_point);

		vertex2d_subtract(&bezier_source_1,next_point,current_point);
		vertex2d_subtract(&bezier_source_2,current_point,previous_point);
		vertex2d_add(&bezier_p1,&bezier_source_1,&bezier_source_2);
		vertex2d_divide(&bezier_p1,&bezier_p1,6);
		vertex2d_add(&bezier_p1,current_point,&bezier_p1);

		vertex2d_subtract(&bezier_source_1,next_point,two_points_forward);
		vertex2d_subtract(&bezier_source_2,current_point,next_point);
		vertex2d_add(&bezier_p2,&bezier_source_1,&bezier_source_2);
		vertex2d_divide(&bezier_p2,&bezier_p2,6);
		vertex2d_add(&bezier_p2,next_point,&bezier_p2);

		for (subpoint_index=0; subpoint_index<256; subpoint_index++) {
			vertex2d_interpolate(&bezier_p0_to_p1,&bezier_p0,&bezier_p1,(double)subpoint_index,SUBPOINTS_PER_POINT);
			vertex2d_interpolate(&bezier_p1_to_p2,&bezier_p1,&bezier_p2,(double)subpoint_index,SUBPOINTS_PER_POINT);
			vertex2d_interpolate(&bezier_p2_to_p3,&bezier_p2,&bezier_p3,(double)subpoint_index,SUBPOINTS_PER_POINT);
			vertex2d_interpolate(&bezier_p0p1_to_p1p2,&bezier_p0_to_p1,&bezier_p1_to_p2,(double)subpoint_index,SUBPOINTS_PER_POINT);
			vertex2d_interpolate(&bezier_p1p2_to_p2p3,&bezier_p1_to_p2,&bezier_p2_to_p3,(double)subpoint_index,SUBPOINTS_PER_POINT);
			vertex2d_interpolate(current_subpoint,&bezier_p0p1_to_p1p2,&bezier_p1p2_to_p2p3,(double)subpoint_index,SUBPOINTS_PER_POINT);
			current_subpoint++;
		}
	}
}

void free_subpoints() {
	free(subpoints);
}
