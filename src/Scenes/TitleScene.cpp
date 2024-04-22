#include "TitleScene.h"

#include "GameScene.h"

void TitleScene::enter() {

}

Scene* TitleScene::update() {
    DrawText("Title SCREEN", 20, 20, 40, RED);
    world.progress();

    if (IsKeyPressed(KEY_SPACE)) {
        return new GameScene(world);
    }

    return nullptr;
}

void TitleScene::exit() {

}