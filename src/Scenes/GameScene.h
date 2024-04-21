#pragma once
#include "Scene.h"
#include "../core/MatchModule.h"
#include "../Match-3/Background.h"
#include "../Match-3/Board.h"
#include "../Match-3/Previewer.h"
#include "../Match-3/Inventory.h"
#include "../Match-3/Button.h"



class GameScene : public Scene {
public:
    Background* background = nullptr;
    Board*      board      = nullptr;
    Inventory*  inventory  = nullptr;
    Previewer*  previewer  = nullptr;

    explicit GameScene(flecs::world& world) : Scene(world) {
        background  = new Background(sceneEntity, C_GREEN);
        board       = new Board(sceneEntity);
        inventory   = new Inventory(sceneEntity, 5);
        previewer   = new Previewer(
                        sceneEntity,
                        3,
                        {C_RED, C_BLUE, C_YELLOW, C_GREEN},
                        {SH_DIAMOND, SH_TRIANGLE, SH_ROUND, SH_KITE}
                     );
    };

    ~GameScene() override {
        delete background;
        delete board;
        delete inventory;
        delete previewer;
    }

private:

    void enter() override;

    Scene* update() override;

    void exit() override;

};