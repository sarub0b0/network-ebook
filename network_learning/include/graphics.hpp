#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>

typedef class window window;
typedef class timer timer;
typedef class event event;
typedef class text text;
// typedef class routing routing;

class graphics {
   private:
    window *window_;
    timer *timer_;
    event *event_;
    text *text_;
    // routing *routing_;

    int frame_count_;

    int fps_;
    int speed_;
    float delta_time_;

    bool done_;

   public:
    graphics();
    ~graphics();

    void init(const std::string *resource_path);
    void loop();
    void shutdown();
    void keyboard_input();
    void mouse_action();
    void update_logic();
    void update_graphics();
};

#endif
