#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

#include "global.h"

void init();
void loop();
void shutdown();

typedef struct point {
    float x, y;
} point_t;

struct object {
    ALLEGRO_BITMAP *bmp;
    char name[MAX_STRLEN];
    int index;
    point_t center;
    point_t dst;
    float angle;
    int w, h;
    int scale_x, scale_y;
    int flags;
};

extern struct object *routers;
extern struct object *paths;
extern struct object *packets;

#endif
