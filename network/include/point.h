#ifndef _POINT_H
#define _POINT_H

typedef struct point {
    float x, y;
} point_t;

float get_length_between_objects(point_t a, point_t b);
point_t add_point(point_t a, point_t b);
point_t sub_point(point_t a, point_t b);
float length_point(point_t a);

point_t get_center_point_between_objects(point_t a, point_t b);
point_t get_center_point_object(point_t dst, int w, int h);
#endif
