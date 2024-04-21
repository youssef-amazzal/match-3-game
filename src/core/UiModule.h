#pragma once
#include "../headers/Header.h"



struct UiModule {

    explicit UiModule(flecs::world& world);

    //====================================//
    //              Components            //
    //====================================//
    struct HBox {};
    struct VBox {};
    struct Text {
        const char* text;
        float fontSize;
        float spacing;
    };

};

using UI = UiModule;