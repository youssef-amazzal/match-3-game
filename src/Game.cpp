#include "Game.h"
#include "Scenes/MainMenu.h"

flecs::world Game::ecs;
Scene* Game::scene = Scene::getInstance<MainMenu>(ecs);
