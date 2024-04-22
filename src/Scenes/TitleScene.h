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
        background  = new Background(sceneEntity, C_GREEN);

        auto buttonContainer = world.entity()
            .is_a<UI::VBox>()
            .add<TM::ContainedBy>(sceneEntity)
            .set<TM::Relative>({TM::Relative::Alignment::CENTER});

        auto subContainer = world.entity().is_a<UI::HBox>();

        newGameButton       = new Button(subContainer, UI_BUTTON,        {C_GREEN}, {2.4, 2.4});
        loadGameButton      = new Button(subContainer, UI_BUTTON,        {C_GREEN}, {2.4, 2.4});
        LeaderboardButton   = new Button(subContainer, UI_ICON_BUTTON,   {IC_LEADERBOARD}, {2.4, 2.4});
        AchievementsButton  = new Button(subContainer, UI_ICON_BUTTON,   {IC_ACHIEVEMENT}, {2.4, 2.4});
        CloseButton         = new Button(subContainer, UI_TEXT_BUTTON_4, {TXT_QUIT}, {2.4, 2.4});

        newGameButton->setContainer(buttonContainer);
        loadGameButton->setContainer(buttonContainer);
        subContainer.add<TM::ContainedBy>(buttonContainer);
        LeaderboardButton->setContainer(subContainer);
        AchievementsButton->setContainer(subContainer);
        CloseButton->setContainer(subContainer);

    }

    ~TitleScene() override {
        delete background;
    }

private:

    void enter() override;

    Scene* update() override;

    void exit() override;
};
