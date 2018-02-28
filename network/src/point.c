#include <math.h>

#include <point.h>

float get_length_between_objects(point_t a, point_t b) {
    point_t p;
    p.x = fabs(a.x - b.x);
    p.y = fabs(a.y - b.y);
    return length_point(p);
}

point_t add_point(point_t a, point_t b) {
    point_t p;
    p.x = a.x + b.x;
    p.y = a.y + b.y;
    return p;
}
point_t sub_point(point_t a, point_t b) {
    point_t p;
    p.x = a.x - b.x;
    p.y = a.y - b.y;
    return p;
}

float length_point(point_t a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

point_t get_center_point_between_objects(point_t a, point_t b) {
    point_t p;
    p.x = fabs(a.x - b.x);
    p.y = fabs(a.y - b.y);
    return p;
}
point_t get_center_point_object(point_t dst, int w, int h) {
    point_t p;
    p.x = dst.x + (w / 2.0);
    p.y = dst.y + (h / 2.0);
    return p;
}
