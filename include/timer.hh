#ifndef TIMER_H_
#define TIMER_H_

typedef struct ALLEGRO_TIMER ALLEGRO_TIMER;
typedef struct ALLEGRO_EVENT_SOURCE ALLEGRO_EVENT_SOURCE;

class timer {
   private:
    ALLEGRO_TIMER *timer_;
    int fps_;

   public:
    timer();
    ~timer();

    void init();
    ALLEGRO_EVENT_SOURCE *get_event_source();
    void start_timer();
};

#endif
