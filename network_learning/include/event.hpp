#ifndef EVENT_H_
#define EVENT_H_

typedef struct ALLEGRO_EVENT_QUEUE ALLEGRO_EVENT_QUEUE;
typedef struct ALLEGRO_EVENT_SOURCE ALLEGRO_EVENT_SOURCE;
typedef union ALLEGRO_EVENT ALLEGRO_EVENT;

class event {
   private:
    ALLEGRO_EVENT_QUEUE *event_queue_;
    ALLEGRO_EVENT *event_;

   public:
    event();
    ~event();

    void init();
    void register_event(ALLEGRO_EVENT_SOURCE *src);
    void wait_for_event();
    int check_event();
    bool is_empty();
    int keyboard_unichar();
    int keyboard_keycode();
};
#endif
