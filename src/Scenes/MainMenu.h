#pragma once
#include "Scene.h"


class MainMenu : public Scene {
public:
    // declared public just so that I can use std::make_unique<MainMenu>()
    MainMenu() : Scene() {}



private:;

    void enter() override;

    Scene* update() override;

    void exit() override;

};