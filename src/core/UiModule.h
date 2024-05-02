#pragma once
#include "../headers/Header.h"



struct UiModule {

    explicit UiModule(flecs::world& world);

    //====================================//
    //               Prefabs              //
    //====================================//
    struct HBox {};
    struct VBox {};


};

using UI = UiModule;