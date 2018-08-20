#include <allegro5/allegro.h>

#include <message.hh>
#include <timer.hh>

timer::timer() : timer_(nullptr), fps_(60) {
}

timer::~timer() {
}

void timer::init(int fps) {
    fps_   = fps;
    timer_ = al_create_timer(1.0 / fps_);
    if (!timer_) throw "Failed to create timer";

    dprintf("fps = %d", fps_);
}

ALLEGRO_EVENT_SOURCE *timer::get_event_source() {
    return al_get_timer_event_source(timer_);
}

void timer::start_timer() {
    al_start_timer(timer_);
}
