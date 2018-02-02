#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

#define FPS 60

void init(void) {
}

void shutdown(void) {
}

void loop(void) {
}

int main(int argc, char **argv) {
    ALLEGRO_DISPLAY *display         = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer             = NULL;
    ALLEGRO_BITMAP *router_img       = NULL;

    bool redraw = true;

    if (!al_init()) {
        al_show_native_message_box(display,
                                   "Error",
                                   "Error",
                                   "Failed to initialize allegro!",
                                   NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        al_show_native_message_box(display,
                                   "Error",
                                   "Error",
                                   "Failed to initialize timer!",
                                   NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(800, 600);
    if (!display) {
        al_show_native_message_box(display,
                                   "Error",
                                   "Error",
                                   "Failed to initialize display!",
                                   NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    if (!al_init_image_addon()) {
        al_show_native_message_box(display,
                                   "Error",
                                   "Error",
                                   "Failed to initialize al_init_image_addon!",
                                   NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    router_img = al_load_bitmap("router.png");

    if (!router_img) {
        al_show_native_message_box(display,
                                   "Error",
                                   "Error",
                                   "Failed to load image!",
                                   NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return 0;
    }

    al_draw_bitmap(router_img, 100, 100, 0);

    al_flip_display();

    al_destroy_display(display);
    al_destroy_bitmap(router_img);

    return 0;
}
