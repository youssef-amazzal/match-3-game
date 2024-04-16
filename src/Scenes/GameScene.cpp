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
        board->push_back(previewer->pop());
    }

    if (IsKeyPressed(KEY_LEFT)) {
        board->push_front(previewer->pop());
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