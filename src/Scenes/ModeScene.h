#pragma once
#include "../headers/Header.h"
#include "Scene.h"

class NewGame;

class ModeScene : public Scene {
public:
    explicit ModeScene(flecs::world& world) : Scene(world) {};

private:

    void enter() override;

    Scene* update() override;

    void exit() override;

};