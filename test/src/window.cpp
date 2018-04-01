#include <cstdio>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include <message.hpp>
#include <window.hpp>

window::window() : display_(nullptr), width_(640), height_(480) {
}

window::window(int w, int h) : display_(nullptr), width_(w), height_(h) {
}

window::~window() {
    al_destroy_display(display_);
}

void window::create() {
    if (!al_init()) {
        al_show_native_message_box(NULL,
                                   "Error",
                                   "Error",
                                   "Failed to initialize allegro!",
                                   NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        throw "failed to initialize allegro!\n";
    }

    dprintf("w:%d h:%d", width_, height_);

    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display_ = al_create_display(width_, height_);

    al_set_window_title(display_, "Network Learning");

    if (!display_) {
        al_show_native_message_box(NULL,
                                   "Error",
                                   "Error",
                                   "Failed to initialize allegro!",
                                   NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        throw "failed to create display!\n";
    }

    al_clear_to_color(al_map_rgb(255, 255, 255));

    al_flip_display();

    al_rest(10.0);
}

void window::print() {
    std::printf("width:%d height:%d display:%p\n", width_, height_, display_);
}
