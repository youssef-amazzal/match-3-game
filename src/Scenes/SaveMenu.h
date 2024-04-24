#pragma once
#include "Scene.h"
#include "../Match-3/Background.h"

class SaveMenu : public Scene {
    Background* background = nullptr;

public:
    explicit SaveMenu(flecs::world& world) : Scene(world) {}

    ~SaveMenu() override {
        delete background;
    }

private:

    void enter() override;

    Scene* update() override;

    void exit() override;

};
