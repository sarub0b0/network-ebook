#include <stdio.h>
#include <math.h>

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

#include "global.h"
#include "message.h"
#include "bitmap.h"
#include "graphics.h"

void init_bitmap();

void get_user_input();
void update_logic();
void update_graphics();

void abort_game(const char *message);

ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer             = NULL;
ALLEGRO_DISPLAY *display         = NULL;

ALLEGRO_BITMAP *router_bmp_ori = NULL;
ALLEGRO_BITMAP *path_bmp_ori   = NULL;
ALLEGRO_BITMAP *packet_bmp_ori = NULL;

ALLEGRO_BITMAP **router_bmp;
ALLEGRO_BITMAP **path_bmp;
ALLEGRO_BITMAP **packet_bmp;

float FPS    = 60;
int SCREEN_W = 640;
int SCREEN_H = 480;

float SPEED = 10;

bool done;

// struct router *routers;

struct object *routers;
struct object *paths;
struct object *packets;

void init(char *resource_path) {
    errno = 0;

    if (!al_init()) abort_game("Failed to initialize allegro");

    if (!al_install_keyboard()) abort_game("Failed to install keyboard");

    if (!al_init_bitmap_addon())
        abort_game("Failed to initialize al_init_bitmap_addon!");

    // al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(640, 480);
    if (!display) abort_game("Failed to create display");
    fprintf(stdout,
            "x:%d y:%d\n",
            al_get_display_width(display),
            al_get_display_height(display));

    timer = al_create_timer(1.0 / FPS);
    if (!timer) abort_game("Failed to create timer");

    event_queue = al_create_event_queue();
    if (!event_queue) abort_game("Failed to create event queue");

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    SCREEN_W = al_get_display_width(display);
    SCREEN_H = al_get_display_height(display);

    char router_image_path[MAX_STRLEN];
    char path_image_path[MAX_STRLEN];
    char packet_image_path[MAX_STRLEN];

    memset(router_image_path, '\0', MAX_STRLEN);
    memset(path_image_path, '\0', MAX_STRLEN);
    memset(packet_image_path, '\0', MAX_STRLEN);

    snprintf(
        router_image_path, MAX_STRLEN, "%s%s", resource_path, "router.png");
    snprintf(path_image_path, MAX_STRLEN, "%s%s", resource_path, "path.png");
    snprintf(
        packet_image_path, MAX_STRLEN, "%s%s", resource_path, "packet.png");

    dprintf("%s\n", router_image_path);
    dprintf("%s\n", path_image_path);
    dprintf("%s\n", packet_image_path);

    router_bmp_ori = al_load_bitmap(router_image_path);
    if (router_bmp_ori == NULL) abort_game("Failed to load router image!");

    path_bmp_ori = al_load_bitmap(path_image_path);
    if (path_bmp_ori == NULL) abort_game("Failed to load path image!");

    packet_bmp_ori = al_load_bitmap(packet_image_path);
    if (packet_bmp_ori == NULL) abort_game("Failed to load packet image!");

    init_bitmap();

    done = false;
}

void init_bitmap() {
    // set initialiezed router
    int router_number, path_number, packet_number;
    router_number = 3;
    path_number   = 3;
    packet_number = 1;

    routers = (struct object *) malloc(sizeof(struct object) * router_number);

    int base_x, base_y, base_w, base_h;
    int path_w, path_h;
    base_x = 10;
    base_y = 10;
    base_w = 200;
    base_h = base_w * sin(60 * M_PI / 180.0);

    path_w = base_w;
    path_h = 8;

    router_bmp     = router_bmp_ori;
    routers[0].bmp = router_bmp;
    routers[1].bmp = router_bmp;
    routers[2].bmp = router_bmp;

    routers[0].index   = 0;
    routers[0].dst.x   = base_x + (base_w / 2.0);
    routers[0].dst.y   = base_y;
    routers[0].angle   = 0.0;
    routers[0].scale_x = 1;
    routers[0].scale_y = 1;
    routers[0].w       = al_get_bitmap_width(router_bmp);
    routers[0].h       = al_get_bitmap_height(router_bmp);
    routers[0].center =
        get_point_obj_center(&routers[0].dst, routers[0].w, routers[0].h);
    routers[0].flags = 0;

    dprintf("router w:%d h:%d\n", routers[0].w, routers[0].h);

    routers[1].index   = 0;
    routers[1].dst.x   = base_x;
    routers[1].dst.y   = base_y + base_h;
    routers[1].angle   = 0.0;
    routers[1].scale_x = 1;
    routers[1].scale_y = 1;
    routers[1].w       = al_get_bitmap_width(router_bmp);
    routers[1].h       = al_get_bitmap_height(router_bmp);
    routers[1].center =
        get_point_obj_center(&routers[1].dst, routers[1].w, routers[1].h);
    routers[1].flags = 0;

    routers[2].index   = 0;
    routers[2].dst.x   = base_x + base_w;
    routers[2].dst.y   = base_y + base_h;
    routers[2].angle   = 0.0;
    routers[2].scale_x = 1;
    routers[2].scale_y = 1;
    routers[2].w       = al_get_bitmap_width(router_bmp);
    routers[2].h       = al_get_bitmap_height(router_bmp);
    routers[2].center =
        get_point_obj_center(&routers[2].dst, routers[2].w, routers[2].h);
    routers[2].flags = 0;

    paths = (struct object *) malloc(sizeof(struct object) * path_number);

    ALLEGRO_BITMAP *tmp_path_bmp;
    tmp_path_bmp = scaled_bitmap(path_bmp_ori, path_w, path_h);
    // path_bmp     = tmp_path_bmp;
    path_bmp = rotated_bitmap(tmp_path_bmp, 60);

    paths[0].index   = 0;
    paths[0].dst.x   = routers[0].center.x;
    paths[0].dst.y   = routers[0].center.y;
    paths[0].angle   = 0.0;
    paths[0].scale_x = 1;
    paths[0].scale_y = 1;
    paths[0].w       = al_get_bitmap_width(path_bmp);
    paths[0].h       = al_get_bitmap_height(path_bmp);
    // paths[0].center  = get_point_obj_center();
    paths[0].flags = 0;

    // dprintf("%d %d\n",
    //         al_get_bitmap_width(path_bmp_ori),
    //         al_get_bitmap_height(path_bmp_ori));
}

void loop(void) {
    bool redraw = true;
    al_start_timer(timer);

    fprintf(stdout,
            "x:%d y:%d\n",
            al_get_display_width(display),
            al_get_display_height(display));

    while (!done) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
            update_logic();
        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                done = true;
            }
            get_user_input();
        } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(255, 255, 255));
            update_graphics();
            al_flip_display();
        }
    }
}

void get_user_input() {
}

void update_logic() {
}

void update_graphics() {

    al_draw_bitmap(path_bmp, paths[0].dst.x, paths[0].dst.y, paths[0].flags);

    al_draw_bitmap(
        router_bmp, routers[0].dst.x, routers[0].dst.y, routers[0].flags);
    al_draw_bitmap(
        router_bmp, routers[1].dst.x, routers[1].dst.y, routers[1].flags);
    al_draw_bitmap(
        router_bmp, routers[2].dst.x, routers[2].dst.y, routers[2].flags);

    // al_draw_bitmap(path_bmp, 0, 0, paths[0].flags);

    // dprintf("path x:%f y:%f\n", paths[0].dst.x, paths[0].dst.y);
    // al_draw_bitmap(path_bmp, 10, 0, 0);

    // al_draw_scaled_bitmap(path_bmp,
    //                       0,
    //                       0,
    //                       al_get_bitmap_width(path_bmp_ori),
    //                       al_get_bitmap_height(path_bmp_ori),
    //                       100,
    //                       100,
    //                       100,
    //                       5,
    //                       0);

    // al_draw_bitmap(router_bmp, 0, 0, 0);
    // al_draw_bitmap(router_bmp, 200, 0, 0);
    // al_draw_bitmap(router_bmp, 0, 200, 0);
    // al_draw_bitmap(router_bmp, 200, 200, 0);

    // srand(0);
    // float dx, dy;
    // dx = SCREEN_W / 10;
    // dy = SCREEN_H / 10;
    // for (int x = 0; x < 10; x++) {
    //     for (int y = 0; y < 10; y++) {
    //         al_draw_bitmap(router_bmp, dx * x, dy * y, 0);
    //     }
    // }
}

void shutdown(void) {
    if (timer) al_destroy_timer(timer);

    if (display) al_destroy_display(display);

    if (event_queue) al_destroy_event_queue(event_queue);

    if (router_bmp_ori) al_destroy_bitmap(router_bmp_ori);
    if (path_bmp_ori) al_destroy_bitmap(path_bmp_ori);
    if (packet_bmp_ori) al_destroy_bitmap(packet_bmp_ori);

    // if (router_bmp) al_destroy_bitmap(router_bmp);
    if (path_bmp) al_destroy_bitmap(path_bmp);
    // if (packet_bmp) al_destroy_bitmap(packet_bmp);

    free(routers);
    free(paths);
    free(packets);
}

void abort_game(const char *message) {
    char msg[MAX_STRLEN];
    snprintf(msg, MAX_STRLEN, "%s\n%s", message, strerror(errno));

    if (!display)
        fprintf(stderr, "%s", msg);
    else
        al_show_native_message_box(
            display, "Error", "Error", msg, NULL, ALLEGRO_MESSAGEBOX_ERROR);
}
