#include "GameScene.h"
#include "ModeScene.h"


//================================//
//             Enter              //
//================================//

void GameScene::enter() {

}

//================================//
//            Update              //
//================================//

Scene* GameScene::update() {
    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);

    if (IsKeyPressed(KEY_RIGHT)) {
        board->push_back(V_COLORS::C_RED, V_SHAPES::SH_DIAMOND);
    }

    if (IsKeyPressed(KEY_LEFT)) {
        board->push_front(V_COLORS::C_BLUE, V_SHAPES::SH_DIAMOND);
    }

    world.progress();

    if (IsKeyPressed(KEY_SPACE)) {
        return new ModeScene(world);
    }

    return nullptr;
}

//================================//
//              Exit              //
//================================//

void GameScene::exit() {
}