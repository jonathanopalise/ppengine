#include <math.h>
#include <stdlib.h>
#include <inttypes.h>
#include "geometry/vertex2d.h"

#define M_PI 3.14159265358979323846
#define SEGMENT_LENGTH 40
#define START_FINISH_LINE_X_DIFFERENCE -1349.705865
#define START_FINISH_LINE_Y_DIFFERENCE 3101.237153
#define START_END_ANGLE_ALIGNMENT_NUMBER 286.1606

struct vertex2d *points;

int allocate_points() {
	points=(struct vertex2d *) malloc(sizeof(struct vertex2d)*256);
	return points!=0;
}

struct vertex2d *get_points() {
	return points;
}

void derive_points_from_track_curve_data(int8_t *track_curve_data) {
	double current_angle=M_PI/2;
	double xpos=0;
	double ypos=0;
	int track_curve_index;
	double segment_xpos_shift=START_FINISH_LINE_X_DIFFERENCE/256;
	double segment_ypos_shift=START_FINISH_LINE_Y_DIFFERENCE/256;

	current_angle=M_PI/2;

	track_curve_index=0;
	while (track_curve_index<256) {
		current_angle+=(double)-track_curve_data[track_curve_index]/START_END_ANGLE_ALIGNMENT_NUMBER;
		xpos+=sin(current_angle)*SEGMENT_LENGTH;
		ypos+=cos(current_angle)*SEGMENT_LENGTH;
		xpos+=segment_xpos_shift;	
		ypos+=segment_ypos_shift;
		if (current_angle<0) {
			current_angle+=M_PI*2;
		} else if (current_angle>M_PI*2) {
			current_angle-=M_PI*2;
		}
		points[track_curve_index].x=xpos;
		points[track_curve_index].y=ypos;
		track_curve_index++;
	}
}

void free_points() {
	free(points);
}
