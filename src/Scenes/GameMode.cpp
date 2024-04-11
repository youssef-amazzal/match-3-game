#include "GameMode.h"
#include "MainMenu.h"
#include "../Game.h"

void GameMode::enter() {
}

Scene* GameMode::update() {
    DrawText("GAME MODE SCREEN", 20, 20, 40, RED);
    Game::ecs.progress();

    if (IsKeyPressed(KEY_SPACE)) {
        return Scene::getInstance<MainMenu>();
    }

    return nullptr;
}

void GameMode::exit() {
}