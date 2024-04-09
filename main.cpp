#include "src/headers/Header.h"

int main() {
    auto world = flecs::world();

    auto hero = world.entity();

    hero.set(Position{4, 5});

    
    return 0;
}
