#include "GameMode.h"
#include "MainMenu.h"

Screen* GameMode::update() {
    DrawText("GAME MODE SCREEN", 20, 20, 40, RED);

    if (IsKeyPressed(KEY_SPACE)) {
        return Screen::getInstance<MainMenu>();
    }

    return nullptr;
}