#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <message.hh>

#include <prompt.hh>
#include <text.hh>

#define INT(x) static_cast<int>(x)
prompt::prompt() : vertical_line_x_(0), is_visible_(false) {
}

prompt::~prompt() {
}

void prompt::init(const std::string *resource_path,
                  int display_w,
                  int display_h) {
    if (!al_init_font_addon()) throw "Failed to initialize font addon";
    if (!al_init_ttf_addon()) throw "Failed to initialize ttf addon";
    if (!al_init_primitives_addon()) throw "Failed to initialize primitive";

    std::string fpath = *resource_path + "/Ricty-Regular.ttf";

    text_.font_size = 28;
    text_.font      = al_load_ttf_font(
        fpath.c_str(), text_.font_size, ALLEGRO_TTF_NO_KERNING);
    if (text_.font == nullptr) throw "Failed to load ttf font";

    text_.ustr     = al_ustr_new("");
    text_.ustr_pos = 0;

    // al_get_ustr_dimensions(
    //     font_, al_ustr_new("A"), &coordinate_x_, &coordinate_y_,
    //     &font_width_, &font_height_);
    text_.font_height = al_get_font_line_height(text_.font);
    text_.font_width  = al_get_text_width(text_.font, "A");

    vertical_line_x_ = 20;
    coordinate_x_    = vertical_line_x_;
    coordinate_y_    = display_h - text_.font_height - 20;
    text_box_width_  = display_w - vertical_line_x_;
    text_box_height_ = coordinate_y_ + text_.font_height;

    vertical_line_x_ = coordinate_x_;

    dprintf("text_box x=%d y=%d w=%d h=%d",
            coordinate_x_,
            coordinate_y_,
            text_box_width_,
            text_box_height_);
}
void prompt::draw_prompt() {
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

    al_draw_ustr(text_.font,
                 al_map_rgb(80, 80, 80),
                 coordinate_x_,
                 coordinate_y_,
                 0,
                 text_.ustr);
}
void prompt::add_char(int unichar) {
    if (al_ustr_length(text_.ustr) < 65 &&
        0 < al_ustr_insert_chr(text_.ustr, text_.ustr_pos++, unichar))
        vertical_line_x_ += text_.font_width;

    // void al_draw_ustr(const ALLEGRO_FONT *font,
    //                   ALLEGRO_COLOR color,
    //                   float x,
    //                   float y,
    //                   int flags,
    //                   const ALLEGRO_USTR *ustr)
}

void prompt::del_char() {
    text_.ustr_pos--;
    if (al_ustr_remove_chr(text_.ustr, text_.ustr_pos))
        vertical_line_x_ -= text_.font_width;
    else
        text_.ustr_pos = 0;
}

void prompt::is_visible(bool is_visible) {
    is_visible_ = is_visible;
}

void prompt::draw_vertical_line() {
    if (is_visible_)
        al_draw_line(vertical_line_x_ + 1,
                     coordinate_y_,
                     vertical_line_x_ + 1,
                     coordinate_y_ + text_.font_height,
                     al_map_rgb(150, 150, 150),
                     3); // command prompt
}

void prompt::move_left_vertical_line() {
    if (0 < text_.ustr_pos) {
        text_.ustr_pos--;
        vertical_line_x_ -= text_.font_width;
    }
}
void prompt::move_right_vertical_line() {
    if (text_.ustr_pos < INT(al_ustr_length(text_.ustr))) {
        text_.ustr_pos++;
        vertical_line_x_ += text_.font_width;
    }
}
