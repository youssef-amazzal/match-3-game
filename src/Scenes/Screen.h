#pragma once
#include "../headers/Header.h"

class Screen {
private:
    bool isPlaying = false;
    virtual void enter() = 0;
    virtual void exit()  = 0;
    virtual Screen* update() = 0;

protected:
    flecs::world world;
    Screen() {
        world = flecs::world();
    }

public:
    virtual ~Screen() = default;

    Screen* play() {

        if (!isPlaying) {
            isPlaying = true;
            enter();
        }

        auto nextScreen = update();

        if (nextScreen) {
            isPlaying = false;
            exit();
        }

        return nextScreen;
    }

};