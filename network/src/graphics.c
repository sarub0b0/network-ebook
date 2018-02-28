#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#include <global.h>
#include <message.h>
#include <bitmap.h>
#include <graphics.h>
#include <point.h>
#include <route.h>
#include <topology.h>

void get_user_input();
void update_logic();
void update_graphics();

void abort_game(const char *message);

ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer             = NULL;
ALLEGRO_DISPLAY *display         = NULL;

ALLEGRO_BITMAP *router_al_bmp_ori = NULL;
ALLEGRO_BITMAP *path_al_bmp_ori   = NULL;
ALLEGRO_BITMAP *packet_al_bmp_ori = NULL;

float FPS    = 60.0;
int SCREEN_W = 640;
int SCREEN_H = 480;

float SPEED = 10;
float DELTA_TIME;

bool done;

void init(char *resource_path) {
    errno = 0;

    router_number = 3;

    DELTA_TIME = 1.0 / FPS;

    if (!al_init()) abort_game("Failed to initialize allegro");

    if (!al_install_keyboard()) abort_game("Failed to install keyboard");

    if (!al_init_image_addon()) abort_game("Failed to initialize al_init_bitmap_addon!");

    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) abort_game("Failed to create display");

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

    snprintf(router_image_path, MAX_STRLEN, "%s%s", resource_path, "router.png");
    snprintf(path_image_path, MAX_STRLEN, "%s%s", resource_path, "path2.png");
    snprintf(packet_image_path, MAX_STRLEN, "%s%s", resource_path, "packet3.png");

    dprintf("window size: %dx%d\n", SCREEN_W, SCREEN_H);
    dprintf("%s\n", router_image_path);
    dprintf("%s\n", path_image_path);
    dprintf("%s\n", packet_image_path);

    router_al_bmp_ori = al_load_bitmap(router_image_path);
    if (router_al_bmp_ori == NULL) abort_game("Failed to load router image!");

    path_al_bmp_ori = al_load_bitmap(path_image_path);
    if (path_al_bmp_ori == NULL) abort_game("Failed to load path image!");

    packet_al_bmp_ori = al_load_bitmap(packet_image_path);
    if (packet_al_bmp_ori == NULL) abort_game("Failed to load packet image!");

    init_topology();
    init_route();

    init_bitmap();

    done = false;
}

void loop(void) {
    bool redraw = true;
    al_start_timer(timer);

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

    for (int i = 0; i < path_number; i++) {
        al_draw_bitmap(
            path_bmps[i].bmp, path_bmps[i].dst.x, path_bmps[i].dst.y, path_bmps[i].flags);
    }

    for (int i = 0; i < router_number; i++) {
        al_draw_bitmap(
            router_bmps[i].bmp, router_bmps[i].dst.x, router_bmps[i].dst.y, router_bmps[i].flags);
    }

    al_draw_bitmap(
        packet_bmps[0].bmp, packet_bmps[0].dst.x, packet_bmps[0].dst.y, packet_bmps[0].flags);
}

void shutdown(void) {
    if (timer) al_destroy_timer(timer);

    if (display) al_destroy_display(display);

    if (event_queue) al_destroy_event_queue(event_queue);

    if (router_al_bmp_ori) al_destroy_bitmap(router_al_bmp_ori);
    if (path_al_bmp_ori) al_destroy_bitmap(path_al_bmp_ori);
    if (packet_al_bmp_ori) al_destroy_bitmap(packet_al_bmp_ori);

    // if (router_bmp) al_destroy_bitmap(router_bmp);
    for (int i = 0; i < path_number; i++) {
        if (path_al_bmps[i]) al_destroy_bitmap(path_al_bmps[i]);
    }
    // if (packet_bmp) al_destroy_bitmap(packet_bmp);

    free(router_bmps);
    free(path_bmps);
    free(packet_bmps);
}

void abort_game(const char *message) {
    char msg[MAX_STRLEN];
    snprintf(msg, MAX_STRLEN, "%s\n%s", message, strerror(errno));

    if (!display)
        fprintf(stderr, "%s", msg);
    else
        al_show_native_message_box(display, "Error", "Error", msg, NULL, ALLEGRO_MESSAGEBOX_ERROR);
}
