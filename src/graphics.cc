#include <vector>
#include <string>
#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <global.hh>
#include <message.hh>
#include <point.hh>
#include <graphics.hh>
#include <window.hh>
#include <timer.hh>
#include <event.hh>
#include <prompt.hh>
#include <routing.hh>

graphics::graphics()
    : window_(new window()),
      timer_(new timer()),
      event_(new event()),
      prompt_(new prompt()),
      routing_(new routing()),
      frame_count_(0),
      fps_(60),
      speed_(10),
      done_(false) {

    delta_time_ = 1.0f / fps_;
}

graphics::~graphics() {
}

void graphics::init(const std::string *resource_path) {
    if (!al_install_keyboard()) throw "Failed to install keyboard";
    if (!al_install_mouse()) throw "Failed to install mouse";
    if (!al_init_image_addon()) throw "Failed to initialize image addon";

    try {
        window_->init();
        timer_->init();
        event_->init();
        prompt_->init(resource_path,
                    window_->display_width(),
                    window_->display_height());
        routing_->init(resource_path,
                       window_->display_width(),
                       window_->display_height());
    } catch (const char *msg) {
        dprintf("%s", msg);
        throw msg;
    }

    event_->register_event(al_get_keyboard_event_source());
    event_->register_event(al_get_mouse_event_source());
    event_->register_event(window_->get_event_source());
    event_->register_event(timer_->get_event_source());
    dprintf("init done");
}

void graphics::loop() {
    bool redraw = true;

    timer_->start_timer();

    dprintf("loop start");
    while (!done_) {
        event_->wait_for_event();

        switch (event_->check_event()) {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                update_logic();
                break;
            case ALLEGRO_EVENT_KEY_CHAR:
                keyboard_input();
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                mouse_action();
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done_ = true;
                break;
            default:
                break;
        }
        if (redraw && event_->is_empty()) {
            redraw = false;
            al_clear_to_color(al_map_rgb(255, 255, 255));
            update_graphics();
            al_flip_display();
        }
    }
}

void graphics::shutdown() {
}
void graphics::keyboard_input() {
    dprintf("unichar %d", event_->keyboard_unichar());
    dprintf("keycode %d", event_->keyboard_keycode());

    if (event_->keyboard_unichar() == 27) done_ = true;

    if (event_->keyboard_unichar() != 0) {
        switch (event_->keyboard_unichar()) {
            case 127: // back space
                prompt_->del_char();
                break;
            case 9:
                break;
            case 13:
                break;
            default:
                prompt_->add_char(event_->keyboard_unichar());
                break;
        }
    } else {
        switch (event_->keyboard_keycode()) {
            case ALLEGRO_KEY_LEFT:
                prompt_->move_left_vertical_line();
                break;
            case ALLEGRO_KEY_RIGHT:
                prompt_->move_right_vertical_line();
                break;
            case ALLEGRO_KEY_UP:
                break;
            case ALLEGRO_KEY_DOWN:
                break;
            default:
                break;
        }
    }
}
void graphics::mouse_action() {
}
void graphics::update_logic() {
    frame_count_++;

    if (0 <= frame_count_ && frame_count_ < 60)
        prompt_->is_visible(true);
    else if (60 <= frame_count_ && frame_count_ < 120)
        prompt_->is_visible(false);
    else
        frame_count_ = 0;

    // dprintf("frame_count_ %d", frame_count_);
}
void graphics::update_graphics() {
    prompt_->draw_prompt();
    routing_->draw_topology();
}
