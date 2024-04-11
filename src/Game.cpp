#include "Game.h"
#include "Scenes/MainMenu.h"

Scene* Game::scene = Scene::getInstance<MainMenu>();
flecs::world Game::ecs;