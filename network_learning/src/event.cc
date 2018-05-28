#include <allegro5/allegro.h>

#include <message.hh>
#include <event.hh>

event::event() : event_queue_(nullptr), event_(nullptr) {
    // event_ = &event;
}

event::~event() {
    delete event_;
}

void event::init() {
    event_       = new ALLEGRO_EVENT;
    event_queue_ = al_create_event_queue();
    if (!event_queue_) throw "Failed to create event_queue";
}

void event::register_event(ALLEGRO_EVENT_SOURCE *src) {
    if (src == nullptr)
        throw "Failed to register event source. event_source is null.";

    al_register_event_source(event_queue_, src);
}

void event::wait_for_event() {
    // delete event_;
    // event_ = new ALLEGRO_EVENT;
    al_wait_for_event(event_queue_, event_);
}

int event::check_event() {
    return event_->type;
}

bool event::is_empty() {
    if (al_is_event_queue_empty(event_queue_)) {
        return true;
    }

    return false;
}

int event::keyboard_unichar() {
    return event_->keyboard.unichar;
}
int event::keyboard_keycode() {
    return event_->keyboard.keycode;
}
