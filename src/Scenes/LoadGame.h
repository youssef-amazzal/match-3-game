#pragma once
#include "Scene.h"
#include "../Match-3/Background.h"

class LoadGame : public Scene {
    Background* background = nullptr;

public:
    explicit LoadGame(flecs::world& world) : Scene(world) {}

    ~LoadGame() override {
        delete background;
    }

private:

    void enter() override;

    Scene* update() override;

    void exit() override;

};
