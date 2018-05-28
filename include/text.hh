#ifndef TEXT_H_
#define TEXT_H_

typedef struct ALLEGRO_FONT ALLEGRO_FONT;
typedef struct _al_tagbstring ALLEGRO_USTR;

typedef struct text {

    ALLEGRO_FONT *font;
    ALLEGRO_USTR *ustr;
    int ustr_pos;
    int font_size;
    int font_width;
    int font_height;

} text_t;

#endif
