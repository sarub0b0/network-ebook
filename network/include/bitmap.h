#ifndef _BITMAP_H
#define _BITMAP_H

#include <global.h>
#include <point.h>

typedef struct ALLEGRO_BITMAP ALLEGRO_BITMAP;

typedef struct bitmap {
    ALLEGRO_BITMAP *bmp;
    char name[MAX_STRLEN];
    int id;
    point_t center;
    point_t dst;
    float angle;
    int w, h;
    int scale_x, scale_y;
    int flags;
} bitmap_t;

typedef struct bitmap_option {
    ALLEGRO_BITMAP *bmp;
    point_t dst;
    int w, h;
}bmp_opt_t;

void init_bitmap();

ALLEGRO_BITMAP *scaled_bitmap(ALLEGRO_BITMAP *original_bmp, int w, int h);
int rotated_bitmap(ALLEGRO_BITMAP *original_bmp, float angle, bmp_opt_t *opt);


#endif
