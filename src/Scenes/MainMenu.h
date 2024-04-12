#pragma once
#include "Scene.h"


class MainMenu : public Scene {
public:
    // declared public just so that I can use std::make_unique<MainMenu>()
    MainMenu(flecs::world& world) : Scene(world) {}



private:;

    void enter() override;

    Scene* update() override;

    void exit() override;

};