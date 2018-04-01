#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <message.hpp>
#include <text.hpp>

text::text()
    : font_(nullptr),
      ustr_(nullptr),
      ustr_pos_(0),
      vertical_line_x_(0),
      font_size_(48),
      is_visible_(false) {
}

text::~text() {
}

void text::init(const std::string *resource_path,
                int display_w,
                int display_h) {
    if (!al_init_font_addon()) throw "Failed to initialize font addon";
    if (!al_init_ttf_addon()) throw "Failed to initialize ttf addon";
    if (!al_init_primitives_addon()) throw "Failed to initialize primitive";

    std::string fpath = *resource_path + "/Ricty-Regular.ttf";

    font_ =
        al_load_ttf_font(fpath.c_str(), font_size_, ALLEGRO_TTF_MONOCHROME);

    if (font_ == nullptr) throw "Failed to load ttf font";

    ustr_ = al_ustr_new("");

    // al_get_ustr_dimensions(
    //     font_, al_ustr_new("A"), &coordinate_x_, &coordinate_y_,
    //     &font_width_, &font_height_);
    font_height_ = al_get_font_line_height(font_);
    font_width_  = al_get_text_width(font_, "A");

    dprintf("font x=%d y=%d w=%d h=%d",
            coordinate_x_,
            coordinate_y_,
            font_width_,
            font_height_);

    vertical_line_x_ = display_w * 0.05;
    coordinate_x_    = vertical_line_x_;
    coordinate_y_    = display_h - font_height_ - 20;
    text_box_width_  = display_w - vertical_line_x_;
    text_box_height_ = coordinate_y_ + font_height_;

    vertical_line_x_ = coordinate_x_;

    dprintf("text_box x=%d y=%d w=%d h=%d",
            coordinate_x_,
            coordinate_y_,
            text_box_width_,
            text_box_height_);
}
void text::draw_textbox() {
    al_draw_rounded_rectangle(coordinate_x_ - 2,
                              coordinate_y_ - 2,
                              text_box_width_ + 2,
                              text_box_height_ + 2,
                              5,
                              5,
                              al_map_rgb(220, 220, 220),
                              10);

    al_draw_filled_rounded_rectangle(coordinate_x_ - 2,
                                     coordinate_y_ - 2,
                                     text_box_width_ + 2,
                                     text_box_height_ + 2,
                                     5,
                                     5,
                                     al_map_rgb(240, 240, 240));
    draw_vertical_line();

    al_draw_ustr(
        font_, al_map_rgb(0, 0, 0), coordinate_x_, coordinate_y_, 0, ustr_);
}
void text::add_text(int unichar) {
    if (0 < al_ustr_insert_chr(ustr_, ustr_pos_++, unichar))
        vertical_line_x_ += font_width_;

    // void al_draw_ustr(const ALLEGRO_FONT *font,
    //                   ALLEGRO_COLOR color,
    //                   float x,
    //                   float y,
    //                   int flags,
    //                   const ALLEGRO_USTR *ustr)
}

void text::del_text() {
    ustr_pos_--;
    if (al_ustr_remove_chr(ustr_, ustr_pos_))
        vertical_line_x_ -= font_width_;
    else
        ustr_pos_ = 0;
}

void text::is_visible(bool is_visible) {
    is_visible_ = is_visible;
}

void text::draw_vertical_line() {
    if (is_visible_)
        al_draw_line(vertical_line_x_ + 1,
                     coordinate_y_ - 1,
                     vertical_line_x_ + 1,
                     coordinate_y_ + font_height_,
                     al_map_rgb(150, 150, 150),
                     3); // command prompt
}

void text::move_left_vertical_line() {
    if (0 < ustr_pos_) {
        ustr_pos_--;
        vertical_line_x_ -= font_width_;
    }
}
void text::move_right_vertical_line() {
    if (ustr_pos_ < al_ustr_length(ustr_)) {
        ustr_pos_++;
        vertical_line_x_ += font_width_;
    }
}
