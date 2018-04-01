#ifndef TEXT_H_
#define TEXT_H_

#include <string>

typedef struct ALLEGRO_FONT ALLEGRO_FONT;
typedef struct _al_tagbstring ALLEGRO_USTR;

class text {
   private:
    ALLEGRO_FONT *font_;
    ALLEGRO_USTR *ustr_;
    int ustr_pos_;
    int vertical_line_x_;
    int font_size_;
    int font_width_;
    int font_height_;
    int coordinate_x_;
    int coordinate_y_;
    int coordinate_offset_x_;
    int text_box_width_;
    int text_box_height_;

    bool is_visible_;

   public:
    text();
    ~text();
    void init(const std::string *resource_path, int display_w, int display_h);
    void draw_textbox();
    void is_visible(bool is_visible);
    void draw_vertical_line();
    void add_text(int unichar);
    void del_text();
    void move_left_vertical_line();
    void move_right_vertical_line();
};

#endif
