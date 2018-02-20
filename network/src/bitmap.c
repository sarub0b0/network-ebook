
#include <math.h>

#include "global.h"
#include "message.h"
#include "bitmap.h"

ALLEGRO_BITMAP *scaled_bitmap(ALLEGRO_BITMAP *original_bmp, int w, int h);
ALLEGRO_BITMAP *rotated_bitmap(ALLEGRO_BITMAP *original_bmp, float angle);

void get_length_between_routers() {
}

point_t get_point_between_objs_center(point_t *a, point_t *b) {
    point_t p;
    p.x = fabs(a->x - b->x);
    p.y = fabs(a->y - b->y);
    return p;
}
point_t get_point_obj_center(point_t *dst, int w, int h) {
    point_t p;
    p.x = dst->x + (w / 2.0);
    p.y = dst->y + (h / 2.0);
    return p;
}

ALLEGRO_BITMAP *rotated_bitmap(ALLEGRO_BITMAP *original_bmp, float angle) {

    ALLEGRO_BITMAP *rotated_bmp, *prev_target;

    // 1. create atemporary bitmap of size we want
    // rotated_bmp = al_create_bitmap(al_get_bitmap_width(original_bmp),
    //                                al_get_bitmap_height(original_bmp));
    int w, h;

    w = al_get_bitmap_width(original_bmp);
    h = al_get_bitmap_height(original_bmp);

    double rad;
    double s, c;

    if (angle < 0) {
        angle += 360;
    }

    rad = angle * M_PI / 180.0;

    s = fabs(sin(rad));
    c = fabs(cos(rad));

    int r_w, r_h;
    r_w = ceil((w * c) + (h * s));
    r_h = ceil((w * s) + (h * c));

    dprintf("rotated_bmp w:%d h:%d\n", r_w, r_h);

    rotated_bmp = al_create_bitmap(r_w, r_h);
    // rotated_bmp = al_create_bitmap(600, 400);
    if (!rotated_bmp) return NULL;

    // 2. load the bitmap at the original size
    // if (!original_bmp) abort_game("Failed to load path.png");

    float dx, dy;
    dx = h * s / 2;
    dy = h * c / 2;

    if (90 < angle && angle <= 180) {
        dx += w * c;
    } else if (180 < angle && angle <= 270) {
        dx += w * c;
        dy += w * s;
    } else if (270 < angle && angle < 360) {
        dy += w * s;
    }

    dprintf("rotated_bmp w:%d h:%d\n",
            al_get_bitmap_width(rotated_bmp),
            al_get_bitmap_height(rotated_bmp));
    // al_draw_bitmap(original_bmp, 0, 0, 0);
    // al_draw_bitmap(original_bmp, dx, dy, 0);

    // 3. set the target bitmap top the rotated bitmap
    prev_target = al_get_target_bitmap();
    al_set_target_bitmap(rotated_bmp);
    al_clear_to_color(al_map_rgba(0, 0, 0, 0));
    // al_clear_to_color(al_map_rgba(255, 255, 255, 0));
    // al_draw_bitmap(rotated_bmp, 300, 0, 0);

    dprintf("rotated_bmp dx:%f dy:%f\n", dx, dy);

    // 4. copy the loaded bitmap to the rotated bitmap

    // al_draw_rotated_bitmap(original_bmp, c.x, c.y, c.x, c.y, angle, 0);
    al_draw_rotated_bitmap(original_bmp, 0, h / 2, dx, dy, rad, 0);

    // al_draw_rotated_bitmap(original_bmp,
    //                        (SCREEN_W / 2.0),
    //                        (SCREEN_H / 2.0),
    //                        dx,
    //                        dy,
    //                        (angle * M_PI / 180.0),
    //                        0);

    // 5. restore the previous target and clean up
    al_set_target_bitmap(prev_target);

    return rotated_bmp;
}

ALLEGRO_BITMAP *scaled_bitmap(ALLEGRO_BITMAP *original_bmp, int w, int h) {
    ALLEGRO_BITMAP *scaled_bmp, *prev_target;

    // 1. create atemporary bitmap of size we want
    scaled_bmp = al_create_bitmap(w, h);
    if (!scaled_bmp) return NULL;

    // 2. load the bitmap at the original size
    // if (!original_bmp) abort_game("Failed to load path.png");

    // 3. set the target bitmap top the scaled bitmap
    prev_target = al_get_target_bitmap();
    al_set_target_bitmap(scaled_bmp);

    // 4. copy the loaded bitmap to the scaled bitmap
    al_draw_scaled_bitmap(original_bmp,
                          0,
                          0,
                          al_get_bitmap_width(original_bmp),
                          al_get_bitmap_height(original_bmp),
                          0,
                          0,
                          w,
                          h,
                          0);

    // 5. restore the previous target and clean up
    al_set_target_bitmap(prev_target);

    return scaled_bmp;
}
