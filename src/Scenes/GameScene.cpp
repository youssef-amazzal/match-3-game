#include "GameScene.h"
#include "ModeScene.h"


//================================//
//             Enter              //
//================================//

void GameScene::enter() {


     world.entity()
        .is_a<UI::HBox>()

        .add<TM::ContainedBy>(sceneEntity)
        .set<TM::Relative>({TM::Relative::Alignment::BOTTOM_CENTER})
        .set<TM::Position, TM::Relative>({0, -100})

        .with<TransformModule::ContainedBy>([&]{
            for (int i = 0; i < 15; i++) {
                world.entity().is_a<UI::PSlot>()
                    .set<RM::Variants>({{ST_SELECTED}});
            }
        });

    world.entity("NextSloat")
        .is_a<UI::PSlot>()
        .set<RM::Variants>({{ST_SELECTED}})
        .set<RM::Scale>({2,2})

        .add<TM::ContainedBy>(sceneEntity)
        .set<TM::Relative>({TM::Relative::Alignment::TOP_LEFT})
        .set<TM::Position, TM::Relative>({50, 50});

    world.entity("Inventory")
        .is_a<UI::VBox>()
        .set<TM::Container::Gap>({5})

        .add<TM::ContainedBy>(sceneEntity)
        .set<TM::Relative>({TM::Relative::Alignment::CENTER_RIGHT})
        .set<TM::Position, TM::Relative>({-30, -50})

        .with<TransformModule::ContainedBy>([&] {
            for (int i = 0; i < 5; i++) {
                world.entity().is_a<UI::PSlot>()
                    .set<RM::Variants>({{ST_OPEN}});
            }
        });



}

//================================//
//            Update              //
//================================//

Scene* GameScene::update() {
    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);

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