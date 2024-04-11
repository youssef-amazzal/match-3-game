#pragma once
#include "../headers/Header.h"
#include "Scene.h"

class MainMenu;

class GameMode : public Scene {
public:
    GameMode() : Scene() {};

private:
    void enter() override;

    Scene * update() override;

    void exit() override;

};