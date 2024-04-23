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
    explicit TitleScene(flecs::world& world) : Scene(world) {
        background  = new Background(sceneEntity, C_BLUE);

        auto buttonContainer = world.entity("buttonContainer")
            .is_a<UI::VBox>()
            .add<TM::ContainedBy>(sceneEntity)
            .set<TM::Relative>({TM::Relative::Alignment::CENTER});

        auto subContainer = world.entity("subContainer").is_a<UI::HBox>();

        newGameButton       = new Button(buttonContainer, "New Game", 7, {3, 3});
        loadGameButton      = new Button(buttonContainer, "Load Game", 7, {3, 3});
        LeaderboardButton   = new Button(subContainer, UI_ICON_BUTTON,   {IC_LEADERBOARD}, {3, 3});
        AchievementsButton  = new Button(subContainer, UI_ICON_BUTTON,   {IC_ACHIEVEMENT}, {3, 3});
        CloseButton         = new Button(subContainer, "Close", 3, {3, 3}, C_RED);

        subContainer.add<TM::ContainedBy>(buttonContainer);

    }

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
