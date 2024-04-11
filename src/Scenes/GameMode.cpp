#include "GameMode.h"
#include "MainMenu.h"
#include "../Game.h"

void GameMode::enter() {
    std::cout << "Enter Game Mode Scene" << "\n";
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
    std::cout << "Exit Game Mode Scene" << "\n";
}