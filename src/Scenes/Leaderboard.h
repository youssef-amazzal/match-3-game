#pragma once
#include "Scene.h"
#include "../Match-3/Background.h"

class Leaderboard : public Scene {
    Background* background = nullptr;

public:
    explicit Leaderboard(flecs::world& world) : Scene(world) {}

    ~Leaderboard() override {
        delete background;
    }

private:

    void enter() override;

    Scene* update() override;

    void exit() override;

};
