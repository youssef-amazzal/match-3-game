#include "ModeScene.h"
#include "GameScene.h"
#include "TitleScene.h"


void ModeScene::enter() {
}

Scene* ModeScene::update() {
    DrawText("GAME MODE SCREEN", 20, 20, 40, RED);
    world.progress();

    if (IsKeyPressed(KEY_SPACE)) {
        return new TitleScene(world);
    }

    return nullptr;
}

void ModeScene::exit() {
}