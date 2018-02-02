#include <iostream>
#include <exception>
#include <stdexcept>

#include "graphics.hpp"

void graphics::init() {
    if (!al_init()) throw "Failed to initialize allegro";
    if (!al_install_keyboard()) throw "Failed to install keyboard";

    timer = al_create_timer(1.0 / fps);
    if (!timer) throw "Failed to create timer";

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(window_w, window_h);
    if (!display) throw "Failed to create display";

    event_queue = al_create_event_queue();
    if (!event_queue) throw "Failed to create event queue";

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    done = false;
}

void graphics::shutdown() {
    if (timer) al_destroy_timer(timer);

    if (display) al_destroy_display(display);

    if (event_queue) al_destroy_event_queue(event_queue);
}

void graphics::loop() {
    bool redraw = true;
    al_start_timer(timer);

    while (!done) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
            // update_logic();
        } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                done = true;
            }
            // get_user_input();
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(255, 255, 255));
            // update_graphics();
            al_flip_display();
        }
    }
}
