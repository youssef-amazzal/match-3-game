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

    newGameButton       = new Button(buttonContainer, "New Game", 7, {3, 3});
    loadGameButton      = new Button(buttonContainer, "Load Game", 7, {3, 3});
    leaderboardButton   = new Button(subContainer, UI_ICON_BUTTON,   {IC_LEADERBOARD}, {3, 3});
    achievementsButton  = new Button(subContainer, UI_ICON_BUTTON,   {IC_ACHIEVEMENT}, {3, 3});
    closeButton         = new Button(subContainer, "Close", 3, {3, 3}, C_RED);

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