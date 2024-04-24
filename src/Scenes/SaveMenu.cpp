#include "SaveMenu.h"

#include "TitleScene.h"

void SaveMenu::enter() {
    background  = new Background(*sceneEntity, C_BLUE);
}

Scene* SaveMenu::update() {
    world.progress();
    DrawText("LOAD GAME SCREEN", 20, 20, 40, RED);

    if (IsKeyPressed(KEY_SPACE)) {
        return new TitleScene(world);
    }
    return nullptr;
}

void SaveMenu::exit() {

}