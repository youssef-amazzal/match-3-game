#include "MainMenu.h"
#include "GameMode.h"
#include "../Game.h"


void MainMenu::enter() {
    auto& ecs = Game::ecs;
    ecs.import<RenderModule>();
    ecs.import<TransformModule>();

    sceneEntity = new flecs::entity;
    *sceneEntity = ecs.entity();

    auto prev = ecs.set_scope(*sceneEntity);

    HUD hud(ecs);

    hud.changeBgColor(C_BLUE);


    auto Slot = ecs.entity("Gem Slot")
            .set<RenderModule::Type>({UI_ELEMENTS::UI_GEM_SLOT})
            .add<RenderModule::Expand>     ()
            .add<RenderModule::Animation>  ()
            .set<TransformModule::Position, TransformModule::World>({100, 100});

    auto Gem = ecs.entity("Gem")
            .child_of(Slot)

            .set<RenderModule::Type>({UI_ELEMENTS::UI_GEM})
            .add<RenderModule::Expand>     ()
            .add<RenderModule::Animation>  ()

            .set<TransformModule::Relative>({TransformModule::Relative::Alignment::CENTER});


    Gem.set<RenderModule::Variants>({.values{C_GREEN, SH_OVAL}});
    Gem.set<RenderModule::Scale>({1.3f, 1.3f});

    ecs.set_scope(prev);

}

Scene* MainMenu::update() {
    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);

    Game::ecs.progress();

    if (IsKeyPressed(KEY_SPACE)) {
    return Scene::getInstance<GameMode>();
    }

    return nullptr;
}

void MainMenu::exit() {
    sceneEntity->destruct();
    delete sceneEntity;
}