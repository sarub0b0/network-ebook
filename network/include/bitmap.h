#ifndef _BITMAP_H
#define _BITMAP_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

#include "graphics.h"

void get_length_between_routers();

point_t get_point_between_objs_center(point_t *a, point_t *b);
point_t get_point_obj_center(point_t *dst, int w, int h);
ALLEGRO_BITMAP *scaled_bitmap(ALLEGRO_BITMAP *original_bmp, int w, int h);
ALLEGRO_BITMAP *rotated_bitmap(ALLEGRO_BITMAP *original_bmp, float angle);

#endif
