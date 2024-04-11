#include "MainMenu.h"
#include "GameMode.h"
#include "../Game.h"
#include "../core/RenderModule.h"
#include "../core/TransformModule.h"

void MainMenu::enter() {
    std::cout << "Enter Main menu Scene" << "\n";

    auto& ecs = Game::ecs;
    ecs.import<RenderModule>();
    ecs.import<TransformModule>();

    sceneEntity = new flecs::entity;
    *sceneEntity = ecs.entity();

    auto prev = ecs.set_scope(*sceneEntity);


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

            .add<TransformModule::Position>()
            .add<TransformModule::Position, TransformModule::World>()
            .set<TransformModule::Relative>({TransformModule::Relative::Alignment::CENTER});

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
    std::cout << "Exit Main menu Scene" << "\n";

    sceneEntity->destruct();
    delete sceneEntity;
}