#include "LoadGame.h"

#include "TitleScene.h"

void LoadGame::enter() {
    background  = new Background(*sceneEntity, C_BLUE);
}

Scene* LoadGame::update() {
    world.progress();
    DrawText("LOAD GAME SCREEN", 20, 20, 40, RED);

    if (IsKeyPressed(KEY_SPACE)) {
        return new TitleScene(world);
    }
    return nullptr;
}

void LoadGame::exit() {

}