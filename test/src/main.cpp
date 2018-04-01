#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include <global.hpp>
#include <message.hpp>
#include <window.hpp>

int main(int argc, char **argv) {
    try {

        window w;
        w.create();
        w.print();

    } catch (...) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
