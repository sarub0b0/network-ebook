#include <iostream>
#include <exception>
#include <stdexcept>

#include "graphics.hpp"

int main(int argc, char **argv) {
    graphics g;

    try {
        g.init();
        g.loop();
        g.shutdown();
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
