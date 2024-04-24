#pragma once
#include "Scene.h"
#include "../core/MatchModule.h"
#include "../Match-3/Background.h"
#include "../Match-3/Board.h"
#include "../Match-3/Previewer.h"
#include "../Match-3/Inventory.h"
#include "../Match-3/Label.h"


class GameScene : public Scene {
    Background* background = nullptr;
    Board*      board      = nullptr;
    Inventory*  inventory  = nullptr;
    Previewer*  previewer  = nullptr;
    Label*      scoreLabel = nullptr;

public:
    explicit GameScene(flecs::world& world) : Scene(world) {}

    ~GameScene() override {
        delete background;
        delete board;
        delete inventory;
        delete previewer;
        delete scoreLabel;
    }

private:

    void enter() override;

    Scene* update() override;

    void exit() override;

};
