#pragma once
#include "Scene.h"
#include "../Match-3/Background.h"
#include "../core/UiModule.h"
#include "../Match-3/Button.h"

struct Background;

class TitleScene : public Scene {
    Background* background      = nullptr;
    Button* newGameButton       = nullptr;
    Button* loadGameButton      = nullptr;
    Button* leaderboardButton   = nullptr;
    Button* achievementsButton  = nullptr;
    Button* closeButton         = nullptr;


public:
    explicit TitleScene(flecs::world& world) : Scene(world) {}

    ~TitleScene() override {
        delete background;
        delete newGameButton;
        delete loadGameButton;
        delete leaderboardButton;
        delete achievementsButton;
        delete closeButton;
    }

private:

    void enter() override;

    Scene* update() override;

    void exit() override;
};
