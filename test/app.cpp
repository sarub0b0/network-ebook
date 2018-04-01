#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>

#include <boost/filesystem.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#define ERROR 1
#define SUCCESS 0

#define MAX_STRING 64

#define dprintf(message...)                      \
    do {                                         \
        std::fprintf(stderr, "%s", __FILE__);    \
        std::fprintf(stderr, "(%d) ", __LINE__); \
        std::fprintf(stderr, "%s: ", __func__);  \
        std::fprintf(stderr, message);           \
        std::fprintf(stderr, "\n");              \
    } while (0)

class window {
   private:
    ALLEGRO_DISPLAY *display_;
    int width_, height_;

   public:
    window(int w, int h) : display_(nullptr), width_(w), height_(h) {
    }
    ~window();

    void create();

    void print();
};
window::~window() {
    al_destroy_display(display_);
}

void window::create() {
    if (!al_init()) {
        al_show_native_message_box(NULL,
                                   "Error",
                                   "Error",
                                   "Failed to initialize allegro!",
                                   NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        throw "failed to initialize allegro!\n";
    }

    dprintf("w:%d h:%d", width_, height_);

    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display_ = al_create_display(width_, height_);

    al_set_window_title(display_, "Network Learning");

    if (!display_) {
        al_show_native_message_box(NULL,
                                   "Error",
                                   "Error",
                                   "Failed to initialize allegro!",
                                   NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        throw "failed to create display!\n";
    }

    al_clear_to_color(al_map_rgb(255, 255, 255));

    al_flip_display();

    al_rest(10.0);
}

void window::print() {
    std::printf("width:%d height:%d display:%p\n", width_, height_, display_);
}
namespace fs = boost::filesystem;

fs::path init_filepath(std::string command) {

    fs::path command_path(command.data());
    fs::path exec_filepath = fs::canonical(command_path);

    fs::path resource_path = exec_filepath.remove_filename().remove_filename();

    resource_path += "/resource";
    return resource_path;
}

int main(int argc, char **argv) {

    std::string command(argv[0]);
    fs::path resource_path(init_filepath(command));

    dprintf("%s", resource_path.string().data());

    try {
        window win = window::window(640, 480);
        win.create();
        win.print();

    } catch (...) {
        std::fprintf(stderr, "Error\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
