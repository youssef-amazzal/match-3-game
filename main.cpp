#include <iostream>
#include <flecs.h>

int main() {
    auto world = flecs::world();

    struct Position {float x, y;};
    struct Velocity {float x, y;};
    struct Health {int hp;};
    struct Hates {};
    struct Dog {};
    struct Attack {int damage;};
    struct Animation {int frame;};
    struct Start {};

    auto hero = world.entity();
    auto orc = world.entity();

    auto invincible = world.entity();
    auto buffed = world.entity();

    hero.set(Position{4, 5});
    hero.set<Attack>(orc, Attack{20});
    hero.set<Start, Animation>(Animation{12});

    
    return 0;
}
