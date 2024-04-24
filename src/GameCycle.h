#pragma once
#include "headers/Header.h"
#include "utils/ResourceManager.h"
#include "Scenes/Scene.h"
#include "core/MatchModule.h"
#include "Scenes/TitleScene.h"

class GameCycle {
public:
    flecs::world world;
private:
    Scene*  scene = nullptr;
    bool    shouldExitCycle = false;
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
        world.import<InputModule>();
        world.import<RenderModule>();
        world.import<AnimationModule>();
        world.import<UiModule>();
        world.import<MatchModule>();
        // WARNING: import Modules first before creating any scene
        // because components needs to be registered first time inside the module
        // instead of the scenes

        scene = new TitleScene(world);
    }

    void run() {

        while (!shouldExitCycle && !WindowShouldClose()) {
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
    void close() {
        CloseWindow();
    }

    void setShouldExit (const bool shouldExit) {
        this->shouldExitCycle = shouldExit;
    }

};

