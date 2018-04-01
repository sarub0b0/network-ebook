#include <string>

#include <allegro5/allegro.h>

#include <global.hpp>
#include <message.hpp>
#include <graphics.hpp>
#include <window.hpp>
#include <timer.hpp>
#include <event.hpp>
#include <text.hpp>
// #include <routing.hpp>
// #include <bitmap.hpp>

graphics::graphics()
    : window_(new window()),
      timer_(new timer()),
      event_(new event()),
      text_(new text()),
      // routing_(new routing()),
      frame_count_(0),
      fps_(60),
      speed_(10),
      done_(false) {

    delta_time_ = 1.0 / fps_;
}

graphics::~graphics() {
}

void graphics::init(const std::string *resource_path) {
    try {
        window_->init();
        timer_->init();
        text_->init(resource_path,
                    window_->display_width(),
                    window_->display_height());
        event_->init();
    } catch (const char *msg) {
        dprintf("%s", msg);
        throw msg;
    }

    if (!al_install_keyboard()) throw "Failed to install keyboard";
    if (!al_install_mouse()) throw "Failed to install mouse";

    event_->register_event(al_get_keyboard_event_source());
    event_->register_event(al_get_mouse_event_source());
    event_->register_event(window_->get_event_source());
    event_->register_event(timer_->get_event_source());
    dprintf("init done");
    // text_->init();
    // routing_->init()
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
            al_clear_to_color(al_map_rgb(0, 0, 0));
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
                text_->del_text();
                break;
            case 9:
                break;
            case 13:
                break;
            // case 85:
            //     break;
            default:
                text_->add_text(event_->keyboard_unichar());
                break;
        }
    } else {
        switch (event_->keyboard_keycode()) {
            case 82: // left key
                text_->move_left_vertical_line();
                break;
            case 83: // right key
                text_->move_right_vertical_line();
                break;
            case 84: // up key
                break;
            case 85: // down key
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
        text_->is_visible(true);
    else if (60 <= frame_count_ && frame_count_ < 120)
        text_->is_visible(false);
    else
        frame_count_ = 0;

    // dprintf("frame_count_ %d", frame_count_);
}
void graphics::update_graphics() {
    text_->draw_textbox();
}
