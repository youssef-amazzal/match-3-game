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
        scoreLabel = new Label(sceneEntity,"999", 200, 10);
    }

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
