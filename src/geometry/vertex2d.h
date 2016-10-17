#ifndef __TRACK_GEOMETRY_VERTEX2D_H
#define __TRACK_GEOMETRY_VERTEX2D_H

struct vertex2d {
	double x;
	double y;
};

double vertex2d_length(struct vertex2d *source);
void vertex2d_multiply(struct vertex2d *result, struct vertex2d *operand, double multiplier);
void vertex2d_divide(struct vertex2d *result, struct vertex2d *operand, double divider);
void vertex2d_subtract(struct vertex2d *result, struct vertex2d *operand1, struct vertex2d *operand2);
void vertex2d_add(struct vertex2d *result,struct vertex2d *operand1, struct vertex2d *operand2);
void vertex2d_rotate_left_90(struct vertex2d *operand);
void vertex2d_reverse(struct vertex2d *operand);
void vertex2d_copy(struct vertex2d *destination, struct vertex2d *source);
void vertex2d_interpolate(struct vertex2d *result,struct vertex2d *point1,struct vertex2d *point2,double fraction_top,double fraction_bottom);

#endif


