#include "MainMenu.h"
#include "GameMode.h"


//================================//
//             Enter              //
//================================//

void MainMenu::enter() {

    HUD hud(world);

    hud.changeBgColor(C_BLUE);


    auto Slot = world.entity("Gem Slot")
            .set<RenderModule::Type>({UI_ELEMENTS::UI_GEM_SLOT})
            .add<RenderModule::Expand>     ()
            .add<RenderModule::Animation>  ()
            .set<RenderModule::Variants>({.values{ST_CLOSED}})
            .set<TransformModule::Position>({100, 100});

    auto Gem = world.entity("Gem")
            .child_of(Slot)

            .set<RenderModule::Type>({UI_ELEMENTS::UI_GEM})
            .add<RenderModule::Expand>     ()
            .add<RenderModule::Animation>  ()
            .set<RenderModule::Variants>({.values{C_GREEN, SH_OVAL}})
            .set<TransformModule::Relative>({TransformModule::Relative::Alignment::CENTER});
}

//================================//
//            Update              //
//================================//

Scene* MainMenu::update() {
    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);

    world.progress();

    if (IsKeyPressed(KEY_SPACE)) {
    return Scene::getInstance<GameMode>(world);
    }

    return nullptr;
}

//================================//
//              Exit              //
//================================//

void MainMenu::exit() {
}