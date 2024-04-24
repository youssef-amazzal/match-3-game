#include "GameScene.h"
#include "ModeScene.h"


//================================//
//             Enter              //
//================================//

void GameScene::enter() {
    background  = new Background(*sceneEntity, C_GREEN);
    board       = new Board(*sceneEntity);
    inventory   = new Inventory(*sceneEntity, 5);
    previewer   = new Previewer(
                    *sceneEntity,
                    3,
                    {C_RED, C_BLUE, C_YELLOW, C_GREEN},
                    {SH_DIAMOND, SH_TRIANGLE, SH_ROUND, SH_KITE}
                 );
    scoreLabel = new Label(*sceneEntity,"999", 200, 10);
}

//================================//
//            Update              //
//================================//

Scene* GameScene::update() {
    if (IsKeyPressed(KEY_RIGHT)) {
        board->push_back(previewer->pop());
    }

    if (IsKeyPressed(KEY_LEFT)) {
        board->push_front(previewer->pop());
    }

    if (IsKeyPressed(KEY_Q)) board->shiftColorLeft(C_RED);
    if (IsKeyPressed(KEY_W)) board->shiftColorLeft(C_BLUE);
    if (IsKeyPressed(KEY_E)) board->shiftColorLeft(C_YELLOW);
    if (IsKeyPressed(KEY_R)) board->shiftColorLeft(C_GREEN);

    if (IsKeyPressed(KEY_A)) board->shiftShapeLeft(SH_DIAMOND);
    if (IsKeyPressed(KEY_S)) board->shiftShapeLeft(SH_TRIANGLE);
    if (IsKeyPressed(KEY_D)) board->shiftShapeLeft(SH_ROUND);
    if (IsKeyPressed(KEY_F)) board->shiftShapeLeft(SH_KITE);

    world.progress();

    if (IsKeyPressed(KEY_SPACE)) {
        return new ModeScene(world);
    }

    board->handleGemMatching();

    return nullptr;
}

//================================//
//              Exit              //
//================================//

void GameScene::exit() {
}