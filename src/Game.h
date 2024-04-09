#pragma once
#include "headers/Header.h"
#include "utils/ResourceManager.h"
#include "Scenes/Screen.h"


class Game {
private:
    static Screen* screen;
public:
    Game() = default;
    ~Game() = default;

    static void init() {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");
        SetTargetFPS(FRAME_RATE);

        // WARNING: If you try to load textures before creating the window, you will face a segmentation fault
        // without any further explanation.

    }
    static void run() {

        while (!WindowShouldClose()) {
            BeginDrawing();

                ClearBackground(RAYWHITE);

                Screen* newScreen = screen->play();

                if (newScreen != nullptr) {
                    screen = newScreen;
                }


            EndDrawing();
        }
    }
    static void exit() {
        CloseWindow();
    }

};

