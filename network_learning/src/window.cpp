#include <cstdio>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include <message.hpp>
#include <window.hpp>

window::window() : display_(nullptr), width_(1280), height_(960) {
}

window::window(int w, int h) : display_(nullptr), width_(w), height_(h) {
}

window::~window() {
    al_destroy_display(display_);
}

void window::init() {

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

}

ALLEGRO_EVENT_SOURCE *window::get_event_source() {
    return al_get_display_event_source(display_);
}

int window::display_width(){
    return al_get_display_width(display_);
}
int window::display_height(){
    return al_get_display_height(display_);
}
void window::print() {
    std::printf("width:%d height:%d display:%p\n", width_, height_, display_);
}
