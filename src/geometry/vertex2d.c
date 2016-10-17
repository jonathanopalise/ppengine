#include <math.h>
#include "geometry/vertex2d.h"

double vertex2d_length(struct vertex2d *source) {
	return sqrt((source->x*source->x)+(source->y*source->y));
}

void vertex2d_multiply(struct vertex2d *result, struct vertex2d *operand, double multiplier) {
	result->x=operand->x*multiplier;
	result->y=operand->y*multiplier;
}

void vertex2d_divide(struct vertex2d *result, struct vertex2d *operand, double divider) {
	result->x=operand->x/divider;
	result->y=operand->y/divider;
}

void vertex2d_subtract(struct vertex2d *result, struct vertex2d *operand1, struct vertex2d *operand2) {
	result->x=operand1->x-operand2->x;
	result->y=operand1->y-operand2->y;
}

void vertex2d_add(struct vertex2d *result,struct vertex2d *operand1, struct vertex2d *operand2) {
	result->x=operand1->x+operand2->x;
	result->y=operand1->y+operand2->y;
}

void vertex2d_rotate_left_90(struct vertex2d *operand) {
	double temp_x;
	double temp_y;
	temp_x=operand->x;
	temp_y=operand->y;
	operand->x=temp_y;
	operand->y=-temp_x;
}

void vertex2d_reverse(struct vertex2d *operand) {
	operand->x=-operand->x;
	operand->y=-operand->y;
}

void vertex2d_copy(struct vertex2d *destination, struct vertex2d *source) {
	destination->x=source->x;
	destination->y=source->y;
}

void vertex2d_interpolate(struct vertex2d *result,struct vertex2d *point1,struct vertex2d *point2,double fraction_top,double fraction_bottom) {
	result->x=point1->x+((point2->x-point1->x)*fraction_top/fraction_bottom);
	result->y=point1->y+((point2->y-point1->y)*fraction_top/fraction_bottom);
}

