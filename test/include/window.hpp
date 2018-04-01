#ifndef WINDOW_H_
#define WINDOW_H_

typedef struct ALLEGRO_DISPLAY ALLEGRO_DISPLAY;

class window {
   private:
    ALLEGRO_DISPLAY *display_;
    int width_, height_;

   public:
    window();
    window(int w, int h);
    ~window();

    void create();

    void print();
};
#endif
