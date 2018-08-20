#ifndef PROMPT_H
#define PROMPT_H

#include <string>

#include <text.hh>

class prompt {
   private:
    text_t text_;

    int vertical_line_x_;

    int coordinate_x_;
    int coordinate_y_;
    // int coordinate_offset_x_;
    int text_box_width_;
    int text_box_height_;

    bool is_visible_;

   public:
    prompt();
    ~prompt();
    void init(const std::string *resource_path, int display_w, int display_h);
    void draw_prompt();
    void is_visible(bool is_visible);
    void draw_vertical_line();
    void add_char(int unichar);
    void del_char();
    void move_left_vertical_line();
    void move_right_vertical_line();
};

#endif
