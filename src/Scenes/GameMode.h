#pragma once
#include "../headers/Header.h"
#include "Screen.h"

class MainMenu;

class GameMode : public Screen {
public:
    GameMode() : Screen() {};

private:
    void enter() override {
        std::cout << "Enter Game mode Screen" << "\n";
    }

    Screen * update() override;

    void exit() override {
        std::cout << "Exit Game mode Screen" << "\n";
    }

};