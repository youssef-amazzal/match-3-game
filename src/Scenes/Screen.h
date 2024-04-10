#pragma once
#include "../headers/Header.h"

class Screen {
    friend class Game;
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

    template<class T>
    static Screen* getInstance() {

        if constexpr (std::is_base_of<Screen, T>::value) {
            static_assert(std::is_base_of<Screen, T>::value, "T must inherit from Screen");
        }

        static std::unique_ptr<Screen> instance = std::make_unique<T>();
        return instance.get();
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