#pragma once
#include "../headers/Header.h"
#include "../core/RenderModule.h"
#include "../core/TransformModule.h"
#include "../core/InputModule.h"

using RD = RenderModule;

struct HUD {

private:
    flecs::entity* bgPattern = nullptr;
    std::vector<flecs::entity*> background;
    flecs::entity* board = nullptr;
    flecs::entity* GemSlot = nullptr;
    flecs::entity* Gem = nullptr;

public:

    explicit HUD(flecs::world& world) {


        // Prefabs
        bgPattern = new flecs::entity;
        *bgPattern = world.entity("BackgroundPattern")
                .set<RenderModule::Type>({UI_ELEMENTS::UI_BG_PATTERN})
                .add<RenderModule::Repeat>()
                .set<RenderModule::Scale>({5.0f, 5.0f})
                .set<TransformModule::Position>({0, 0});

        // correction
        bgPattern->get_mut<RenderModule::Sprite>()->repeat = true;
    }

    ~HUD() {
        delete bgPattern;
        for (auto& bg : background) {
            delete bg;
        }
        delete board;
        delete GemSlot;
        delete Gem;
    }

    void changeBgColor(V_COLORS color) {
        bgPattern->set<RenderModule::Variants>({.values{color}});
    }

    void buildBoard(flecs::world& world) {

    }

    struct Container {

    };

};