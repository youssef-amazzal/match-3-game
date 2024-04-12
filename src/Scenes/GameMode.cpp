#include "GameMode.h"
#include "MainMenu.h"



void GameMode::enter() {
}

Scene* GameMode::update() {
    DrawText("GAME MODE SCREEN", 20, 20, 40, RED);
    world.progress();

    if (IsKeyPressed(KEY_SPACE)) {
        return new MainMenu(world);
    }

    return nullptr;
}

void GameMode::exit() {
}