#include "MainMenu.h"
#include "GameMode.h"

Screen* MainMenu::update() {
    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);

    if (IsKeyPressed(KEY_SPACE)) {
    return GameMode::getInstance();
    }

    return nullptr;
}