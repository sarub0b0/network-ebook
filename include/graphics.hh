#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <vector>
#include <string>

class window;
class timer;
class event;
class prompt;
class routing;

class graphics {
   private:
    window *window_;
    timer *timer_;
    event *event_;
    prompt *prompt_;
    routing *routing_;

    int frame_count_;

    int fps_;
    int speed_;
    float delta_time_;

    bool done_;

    void mouse_action();
    void keyboard_input();
    void update_logic();
    void update_graphics();

   public:
    graphics();
    ~graphics();

    void init(const std::string *resource_path);
    void loop();
    void shutdown();
};

#endif
