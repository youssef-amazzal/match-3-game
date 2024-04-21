#include "GameScene.h"
#include "ModeScene.h"


//================================//
//             Enter              //
//================================//

void GameScene::enter() {
//    //shapes: diamond, triangle, round, kite
//    //colors: red, blue, yellow, green
//    // DR, TY, DG, RR, DB, TG
//
//    Gem gems[] = {
//            Gem(world, C_RED, SH_DIAMOND),
//            Gem(world, C_YELLOW, SH_TRIANGLE),
//            Gem(world, C_GREEN, SH_DIAMOND),
//            Gem(world, C_RED, SH_ROUND),
//            Gem(world, C_BLUE, SH_DIAMOND),
//            Gem(world, C_GREEN, SH_TRIANGLE),
//    };
//
//    for (auto & gem : gems) {
//        board->push_back(gem);
//    }
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

//    DrawTextPro(Font "SCORE", 20, 20, 40, DARKGREEN);


    return nullptr;
}

//================================//
//              Exit              //
//================================//

void GameScene::exit() {
}