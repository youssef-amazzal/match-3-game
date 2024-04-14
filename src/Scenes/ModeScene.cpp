#include "ModeScene.h"
#include "GameScene.h"



void ModeScene::enter() {
}

Scene* ModeScene::update() {
    DrawText("GAME MODE SCREEN", 20, 20, 40, RED);
    world.progress();

    if (IsKeyPressed(KEY_SPACE)) {
        return new GameScene(world);
    }

    return nullptr;
}

void ModeScene::exit() {
}