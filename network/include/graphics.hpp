#ifndef _GRAPHICS_HPP
#define _GRAPHICS_HPP

#include "allegro5/allegro5.h"
#include "allegro5/allegro_native_dialog.h"

class graphics {
   private:
    bool done;
    int fps;

   public:
    ALLEGRO_MUTEX *mutex;
    ALLEGRO_COND *cond;

    ALLEGRO_DISPLAY *display;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *event_queue;

    int window_w, window_h;

    graphics();
    ~graphics();

    void init();
    void shutdown();
    void loop();
    void update_graphic();
    void update_logic();
    void get_user_input();
};

#endif
