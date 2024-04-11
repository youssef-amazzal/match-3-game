#include "MainMenu.h"
#include "GameMode.h"
#include "../Game.h"
#include "../core/RenderModule.h"

void MainMenu::enter() {
    std::cout << "Enter Main menu Scene" << "\n";

    auto& ecs = Game::ecs;
    ecs.import<RenderModule>();
    sceneEntity = new flecs::entity;
    *sceneEntity = ecs.entity();

    auto prev = ecs.set_scope(*sceneEntity);

    auto UiElement = ecs.entity()
            .set<RenderModule::Type>      ({UI_ELEMENTS::UI_BUTTON, 0})
            .add<RenderModule::Sprite>    ()
            .set<RenderModule::Variants>  ({.values = {C_RED}})
            .add<RenderModule::Expand>    ()
            .add<RenderModule::Animation> ();

    ecs.set_scope(prev);
    RenderModule::init(ecs);
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