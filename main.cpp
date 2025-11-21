#include <exception>
#include <iostream>

#include "Game.h"

int main() {
    try {
        Game game;
        return game.run();
    }
    catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << std::endl;
        return -1;
    }
    catch (...) {
        std::cerr << "Fatal error: Unknown exception" << std::endl;
        return -1;
    }
}