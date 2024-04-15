#pragma once
#include "headers/Header.h"
#include "utils/ResourceManager.h"
#include "Scenes/Scene.h"
#include "Scenes/GameScene.h"
#include "core/MatchModule.h"

class GameCycle {
public:
    flecs::world world;
private:
    Scene* scene = nullptr;
public:
    GameCycle() = default;

    ~GameCycle() = default;

    static GameCycle& getInstance() {
        static GameCycle instance;
        return instance;
    }

    void init() {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");
        SetTargetFPS(FRAME_RATE);
        // WARNING: If you try to load textures before creating the window, you will face a segmentation fault
        // without any further explanation.
        RSC::loadTextures();

        world.import<TransformModule>();
        world.import<RenderModule>();
        world.import<UiModule>();
        world.import<MatchModule>();
        // WARNING: import Modules first before creating any scene
        // because components needs to be registered first time inside the module
        // instead of the scenes

        scene = new GameScene(world);

    }

    void run() {

        while (!WindowShouldClose()) {
            BeginDrawing();

                ClearBackground(RAYWHITE);

                Scene* newScene = scene->play();
                if (newScene != nullptr) {
                    auto oldScene = scene;
                    scene = newScene;
                    delete oldScene;
                }


            EndDrawing();
        }
    }
    static void exit() {
        CloseWindow();
    }


};

