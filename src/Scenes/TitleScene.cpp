#include "TitleScene.h"

#include "GameScene.h"
#include "Leaderboard.h"
#include "SaveMenu.h"
#include "../GameCycle.h"

void TitleScene::enter() {
    background  = new Background(*sceneEntity, C_BLUE);

    auto buttonContainer = world.entity("buttonContainer")
        .is_a<UI::VBox>()
        .add<TM::ContainedBy>(*sceneEntity)
        .set<TM::Relative>({TM::Relative::Alignment::CENTER});

    auto subContainer = world.entity("subContainer").is_a<UI::HBox>();

    newGameButton       = &(new Button(buttonContainer,7))->setLabel("New Game");
    loadGameButton      = &(new Button(buttonContainer,7))->setLabel("Load Game");
    leaderboardButton   = new Button(subContainer, UI_ICON_BUTTON,   {IC_LEADERBOARD});
    achievementsButton  = new Button(subContainer, UI_ICON_BUTTON,   {IC_ACHIEVEMENT});
    closeButton         = &(new Button(subContainer, 3))->setLabel("Close").setVariant({C_RED});

    subContainer.add<TM::ContainedBy>(buttonContainer);
}

Scene* TitleScene::update() {
    DrawText("Title SCREEN", 20, 20, 40, RED);
    world.progress();

    if (newGameButton->isClicked()) {
        return new GameScene(world);
    }

    if (loadGameButton->isClicked()) {
        return new SaveMenu(world);
    }

    if (leaderboardButton->isClicked()) {
        return new Leaderboard(world);
    }

    if (closeButton->isClicked()) {
        GameCycle::getInstance().setShouldExit(true);
    }

    return nullptr;
}

void TitleScene::exit() {

}