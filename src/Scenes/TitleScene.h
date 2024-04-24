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
    Button* LeaderboardButton   = nullptr;
    Button* AchievementsButton  = nullptr;
    Button* CloseButton         = nullptr;


public:
    explicit TitleScene(flecs::world& world) : Scene(world) {}

    ~TitleScene() override {
        delete background;
        delete newGameButton;
        delete loadGameButton;
        delete LeaderboardButton;
        delete AchievementsButton;
        delete CloseButton;
    }

private:

    void enter() override;

    Scene* update() override;

    void exit() override;
};
