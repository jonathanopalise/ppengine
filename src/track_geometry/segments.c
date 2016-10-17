#include <math.h>
#include <stdlib.h>
#include "track_geometry/segments.h"

#define SEGMENT_WIDTH_IN_WORLD_COORDINATES 20

struct segment *segments;

int allocate_segments() {
	segments=(struct segment *) malloc(sizeof(struct segment)*NUMBER_OF_SEGMENTS);
	return segments!=0;
}

struct segment *get_segments() {
	return segments;
}

void derive_segments_from_subpoints(struct vertex2d *subpoints) {
	struct vertex2d* current_subpoint;
	struct vertex2d* next_subpoint;
	struct segment *current_segment;
	struct vertex2d forward_vector;
	int segment_index;

	current_segment=get_segments();
	for (segment_index=0; segment_index<65536; segment_index++) {
		current_subpoint=&subpoints[segment_index];
		next_subpoint=&subpoints[(segment_index+1)&65535];

		vertex2d_subtract(&forward_vector,next_subpoint,current_subpoint);
		vertex2d_multiply(&forward_vector,&forward_vector,1.0/vertex2d_length(&forward_vector));
		current_segment->angle_radians=atan2(forward_vector.y,forward_vector.x);
		vertex2d_copy(&current_segment->centre,current_subpoint);
		vertex2d_copy(&current_segment->track_left_edge,&forward_vector);
		vertex2d_multiply(&current_segment->track_left_edge,&current_segment->track_left_edge,SEGMENT_WIDTH_IN_WORLD_COORDINATES/2);
		vertex2d_rotate_left_90(&current_segment->track_left_edge);
		vertex2d_copy(&current_segment->track_right_edge,&current_segment->track_left_edge);
		vertex2d_reverse(&current_segment->track_right_edge);
		vertex2d_add(&current_segment->track_left_edge,current_subpoint,&current_segment->track_left_edge);
		vertex2d_add(&current_segment->track_right_edge,current_subpoint,&current_segment->track_right_edge);

		current_segment++;
	}
}

void free_segments() {
	free(segments);
}
