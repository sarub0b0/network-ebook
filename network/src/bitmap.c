#include <math.h>

#include <global.h>
#include <message.h>
#include <graphics.h>

#include <bitmap.h>
include <point.h>

void print_bitmap();

ALLEGRO_BITMAP **router_al_bmps;
ALLEGRO_BITMAP **path_al_bmps;
ALLEGRO_BITMAP **packet_al_bmps;

int router_number, path_number, packet_number;

bitmap_t *router_bmps;
bitmap_t *path_bmps;
bitmap_t *packet_bmps;

void init_bitmap() {
    router_number = 3;
    path_number   = 3;
    packet_number = 1;

    router_al_bmps = (ALLEGRO_BITMAP **) malloc(sizeof(ALLEGRO_BITMAP *) * router_number);
    path_al_bmps   = (ALLEGRO_BITMAP **) malloc(sizeof(ALLEGRO_BITMAP *) * path_number);
    packet_al_bmps = (ALLEGRO_BITMAP **) malloc(sizeof(ALLEGRO_BITMAP *) * packet_number);

    router_bmps = (bitmap_t *) malloc(sizeof(bitmap_t) * router_number);
    path_bmps   = (bitmap_t *) malloc(sizeof(bitmap_t) * path_number);
    packet_bmps = (bitmap_t *) malloc(sizeof(bitmap_t) * packet_number);

    int base_x, base_y, base_w, base_h;
    int router_w, router_h;
    int path_w, path_h;
    int packet_w, packet_h;

    dprintf("window size: %dx%d\n", SCREEN_W, SCREEN_H);
    base_x = SCREEN_W / 15;
    base_y = SCREEN_H / 15;
    base_w = SCREEN_W / 3;
    base_h = base_w * sin(60 * M_PI / 180.0);

    path_w = base_w;
    path_h = SCREEN_H / 20;

    router_w = SCREEN_W / 10;
    router_h = router_w;

    packet_w = SCREEN_W / 10;
    packet_h = path_w / 7;

    ALLEGRO_BITMAP *tmp_router_bmp;
    tmp_router_bmp = scaled_bitmap(router_al_bmp_ori, router_w, router_h);

    for (int i = 0; i < router_number; i++) {
        router_al_bmps[i] = tmp_router_bmp;
        switch (i) {
            case 0:
                router_bmps[i].dst.x = base_x + (base_w / 2.0);
                router_bmps[i].dst.y = base_y;
                break;
            case 1:
                router_bmps[i].dst.x = base_x;
                router_bmps[i].dst.y = base_y + base_h;
                break;
            case 2:
                router_bmps[i].dst.x = base_x + base_w;
                router_bmps[i].dst.y = base_y + base_h;
                break;
            default:
                break;
        }

        router_bmps[i].bmp     = router_al_bmps[i];
        router_bmps[i].id      = i;
        router_bmps[i].angle   = 0.0;
        router_bmps[i].scale_x = 1;
        router_bmps[i].scale_y = 1;
        router_bmps[i].w       = al_get_bitmap_width(router_al_bmps[i]);
        router_bmps[i].h       = al_get_bitmap_height(router_al_bmps[i]);
        router_bmps[i].center =
            get_center_point_object(router_bmps[i].dst, router_bmps[i].w, router_bmps[i].h);
        router_bmps[i].flags = 0;
    }

    int angle;
    ALLEGRO_BITMAP *tmp_path_bmp;
    bmp_opt_t opt;

    tmp_path_bmp = scaled_bitmap(path_al_bmp_ori, path_w, path_h);

    for (int i = 0; i < path_number; i++) {
        switch (i) {
            case 0:
                angle = 120;
                rotated_bitmap(tmp_path_bmp, angle, &opt);

                path_al_bmps[i]    = opt.bmp;
                path_bmps[i].dst.x = router_bmps[0].center.x - opt.dst.x;
                path_bmps[i].dst.y = router_bmps[0].center.y;
                break;
            case 1:
                angle              = 0;
                path_al_bmps[i]    = tmp_path_bmp;
                path_bmps[i].dst.x = router_bmps[1].center.x;
                path_bmps[i].dst.y = router_bmps[1].center.y - path_h / 2;
                break;
            case 2:
                angle = 60;
                rotated_bitmap(tmp_path_bmp, angle, &opt);
                path_al_bmps[i]    = opt.bmp;
                path_bmps[i].dst.x = router_bmps[0].center.x - opt.dst.x;
                path_bmps[i].dst.y = router_bmps[0].center.y;
                break;
            default:
                break;
        }
        path_bmps[i].bmp     = path_al_bmps[i];
        path_bmps[i].id      = i;
        path_bmps[i].angle   = angle;
        path_bmps[i].scale_x = 1;
        path_bmps[i].scale_y = 1;
        path_bmps[i].w       = al_get_bitmap_width(path_al_bmps[i]);
        path_bmps[i].h       = al_get_bitmap_height(path_al_bmps[i]);
        path_bmps[i].flags   = 0;
    }

    ALLEGRO_BITMAP *tmp_packet_bmp;
    tmp_packet_bmp = scaled_bitmap(packet_al_bmp_ori, packet_w, packet_h);

    packet_al_bmps[0] = tmp_packet_bmp;

    packet_bmps[0].bmp     = packet_al_bmps[0];
    packet_bmps[0].dst.x   = 10;
    packet_bmps[0].dst.y   = 10;
    packet_bmps[0].angle   = angle;
    packet_bmps[0].scale_x = 1;
    packet_bmps[0].scale_y = 1;
    packet_bmps[0].w       = al_get_bitmap_width(packet_al_bmps[0]);
    packet_bmps[0].h       = al_get_bitmap_height(packet_al_bmps[0]);
    packet_bmps[0].flags   = 0;
}
int rotated_bitmap(ALLEGRO_BITMAP *original_bmp, float angle, bmp_opt_t *opt) {

    ALLEGRO_BITMAP *rotated_bmp, *prev_target;

    // 1. create atemporary bitmap of size we want
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

    // dprintf("rotated_bmp w:%d h:%d\n", r_w, r_h);

    rotated_bmp = al_create_bitmap(r_w, r_h);
    // rotated_bmp = al_create_bitmap(600, 400);
    if (!rotated_bmp) return ERROR;

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

    // dprintf("rotated_bmp w:%d h:%d\n",
    //         al_get_bitmap_width(rotated_bmp),
    //         al_get_bitmap_height(rotated_bmp));

    // 3. set the target bitmap top the rotated bitmap
    prev_target = al_get_target_bitmap();
    al_set_target_bitmap(rotated_bmp);
    al_clear_to_color(al_map_rgba(0, 0, 0, 0));
    // al_clear_to_color(al_map_rgba(255, 255, 255, 0));
    // al_draw_bitmap(rotated_bmp, 300, 0, 0);

    // dprintf("rotated_bmp dx:%f dy:%f\n", dx, dy);

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

    opt->bmp   = rotated_bmp;
    opt->dst.x = dx;
    opt->dst.y = dy;
    opt->w     = r_w;
    opt->h     = r_h;

    return SUCCESS;
}

ALLEGRO_BITMAP *scaled_bitmap(ALLEGRO_BITMAP *original_bmp, int w, int h) {
    ALLEGRO_BITMAP *scaled_bmp, *prev_target;

    // 1. create atemporary bitmap of size we want
    scaled_bmp = al_create_bitmap(w, h);
    if (!scaled_bmp) return NULL;

    // 2. load the bitmap at the original size

    // 3. set the target bitmap top the scaled bitmap
    prev_target = al_get_target_bitmap();
    al_set_target_bitmap(scaled_bmp);
    al_clear_to_color(al_map_rgba(0, 0, 0, 0));

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

void print_bitmap() {
}
