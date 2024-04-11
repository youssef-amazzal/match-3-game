#pragma once
#include "../headers/Header.h"

struct InputModule {

        explicit InputModule(flecs::world& world) {
            world.component<Mouse>("Mouse");
            world.component<Keyboard>("Keyboard");

//            world.set<Mouse>({}); // Singleton
        }

        struct Mouse;
        struct Keyboard;

private:


public:

        struct Mouse {};
        struct Keyboard {};
};