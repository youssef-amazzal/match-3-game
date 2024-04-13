#include "MainMenu.h"
#include "GameMode.h"


//================================//
//             Enter              //
//================================//

void MainMenu::enter() {

    HUD hud(world);

    hud.changeBgColor(C_BLUE);

     auto Board = world.entity("Board 1")
                .add<TransformModule::ContainedBy>(sceneEntity)
                .add<TransformModule::Container>()
                .set<TransformModule::Container::Alignment>({TransformModule::Container::Alignment::Type::ROW})
                .set<TransformModule::Container::Gap>({5})
                .add<TransformModule::Area>()
                .set<TransformModule::Relative>({TransformModule::Relative::Alignment::BOTTOM_CENTER})
                .set<TransformModule::Position, TransformModule::Relative>({0, -100})
                .with<TransformModule::ContainedBy>([&]{
                    for (int i = 0; i < 5; i++) {
                        auto Slot = world.entity()
                            .set<RenderModule::Type>({UI_ELEMENTS::UI_GEM_SLOT})
                            .set<RenderModule::Variants>({.values{ST_CLOSED}})

                            .set<TransformModule::Relative>({TransformModule::Relative::Alignment::CENTER})
                            .set<TransformModule::Position>({100, 100})
                            .with<TransformModule::ContainedBy>([&]{
//                                auto Gem = world.entity()
//                                        .set<RenderModule::Type>({UI_ELEMENTS::UI_GEM})
//                                        .set<RenderModule::Variants>({.values{C_GREEN, SH_OVAL}})
//                                        .set<TransformModule::Relative>({TransformModule::Relative::Alignment::CENTER});
                            });
                    }
                });

//    auto Board = world.entity("Board 1")
//            .add<TransformModule::ContainedBy>(sceneEntity)
//            .set<TransformModule::Container>({
//                .items = {},
//                .alignment = TransformModule::Container::Alignment::COL_REV,
//                .fixed = false
//            })
//            .add<TransformModule::Area>()
//            .set<TransformModule::Relative>({TransformModule::Relative::Alignment::BOTTOM_CENTER})
//            .set<TransformModule::Position, TransformModule::Relative>({0, -100});
//
//
    auto Slot1 = world.entity("Slot1")
            .set<RenderModule::Type>({UI_ELEMENTS::UI_GEM_SLOT})
            .set<RenderModule::Variants>({.values{ST_CLOSED}})

            .add<TransformModule::ContainedBy>(Board)
            .set<TransformModule::Relative>({TransformModule::Relative::Alignment::CENTER});

    auto Gem1 = world.entity("Gem1")
            .child_of(Slot1)

            .set<RenderModule::Type>({UI_ELEMENTS::UI_GEM})
            .set<RenderModule::Variants>({.values{C_RED, SH_HEART}})

            .add<TransformModule::ContainedBy>(Slot1)
            .set<TransformModule::Relative>({TransformModule::Relative::Alignment::CENTER});

    auto NextSloat = world.entity("NextSloat")
            .set<RenderModule::Type>({UI_ELEMENTS::UI_GEM_SLOT})
            .set<RenderModule::Variants>({.values{ST_OPEN}})
            .set<RenderModule::Scale>({2,2})

            .add<TransformModule::ContainedBy>(sceneEntity)
            .set<TransformModule::Relative>({TransformModule::Relative::Alignment::TOP_LEFT})
            .set<TransformModule::Position, TransformModule::Relative>({50, 50});


}

//================================//
//            Update              //
//================================//

Scene* MainMenu::update() {
    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);

    world.progress();

    if (IsKeyPressed(KEY_SPACE)) {
        return new GameMode(world);
    }

    return nullptr;
}

//================================//
//              Exit              //
//================================//

void MainMenu::exit() {
}