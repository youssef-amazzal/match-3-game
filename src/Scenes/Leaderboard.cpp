#include "Leaderboard.h"
#include "TitleScene.h"

void Leaderboard::enter() {
    background  = new Background(*sceneEntity, C_BLUE);
}

Scene* Leaderboard::update() {
    world.progress();
    DrawText("Leaderboard SCREEN", 20, 20, 40, RED);

    if (IsKeyPressed(KEY_SPACE)) {
        return new TitleScene(world);
    }
    return nullptr;
}

void Leaderboard::exit() {

}