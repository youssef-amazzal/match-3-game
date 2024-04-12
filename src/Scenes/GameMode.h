#pragma once
#include "../headers/Header.h"
#include "Scene.h"

class MainMenu;

class GameMode : public Scene {
public:
    GameMode(flecs::world& world) : Scene(world) {};

private:

    void enter() override;

    Scene* update() override;

    void exit() override;

};