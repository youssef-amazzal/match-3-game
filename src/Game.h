#pragma once
#include "headers/Header.h"
#include "utils/ResourceManager.h"
#include "Scenes/Scene.h"

class Game {
public:
    static flecs::world ecs;
private:
    static Scene* scene;
public:
    Game() = default;
    ~Game() = default;

    static void init() {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");
        SetTargetFPS(FRAME_RATE);

        // WARNING: If you try to load textures before creating the window, you will face a segmentation fault
        // without any further explanation.
        RSC::loadTextures();


        ecs.import<RenderModule>();
        ecs.import<TransformModule>();

    }

    static void run() {

        while (!WindowShouldClose()) {
            BeginDrawing();

                ClearBackground(RAYWHITE);

                Scene* newScene = scene->play();
                if (newScene != nullptr) {
                    scene = newScene;
                }


            EndDrawing();
        }
    }
    static void exit() {
        CloseWindow();
    }


};

