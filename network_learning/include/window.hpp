#ifndef WINDOW_H_
#define WINDOW_H_

typedef struct ALLEGRO_DISPLAY ALLEGRO_DISPLAY;
typedef struct ALLEGRO_EVENT_SOURCE ALLEGRO_EVENT_SOURCE;

class window {
   private:
    ALLEGRO_DISPLAY *display_;
    int width_, height_;

   public:
    window();
    window(int w, int h);
    ~window();

    void init();

    ALLEGRO_EVENT_SOURCE *get_event_source();

    int display_width();
    int display_height();

    void print();
};
#endif
