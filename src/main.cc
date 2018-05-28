#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>

#include <boost/filesystem.hpp>
// #include <experimental/filesystem>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include <global.hh>
#include <message.hh>

#include <graphics.hh>

// namespace fs = std::experimental::filesystem;
namespace fs = boost::filesystem;

fs::path init_filepath(std::string command);

int main(int argc, char **argv) {
    std::string command(argv[0]);
    fs::path resource_path(init_filepath(command));

    dprintf("%s", resource_path.string().data());

    try {
        if (!al_init()) {
            throw "failed to initialize allegro!\n";
        }

        graphics *g = new graphics();
        g->init(&resource_path.string());
        g->loop();

    } catch (const char *msg) {
        al_show_native_message_box(NULL, "Error", "Error", msg, NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

fs::path init_filepath(std::string command) {

    fs::path command_path(command.data());
    fs::path exec_filepath = fs::canonical(command_path);

    fs::path resource_path = exec_filepath.remove_filename().remove_filename();

    resource_path += "/resource";
    return resource_path;
}
