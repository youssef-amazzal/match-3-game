#pragma once
#include "../headers/Header.h"
#include "../core/RenderModule.h"
#include "../core/TransformModule.h"
#include "../core/InputModule.h"

using RM = RenderModule;
using TM = TransformModule;

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
        world.prefab<Slot>("Slot")
                .set<RM::Type>({UI_ELEMENTS::UI_GEM_SLOT})
                .set_override<RM::Variants>({.values{ST_OPEN}})
                .set_override<TM::Position>({0, 0});

        world.prefab<Board>("Board")
                .set_override<TM::Position>({0, 0})
                .set_override<TM::Relative>({TM::Relative::Alignment::BOTTOM_CENTER})
                .set_override<TM::Position, TM::Relative>({0, -100});

        // Prefabs
        bgPattern = new flecs::entity;
        *bgPattern = world.entity("BackgroundPattern")
                .set<RM::Type>({UI_ELEMENTS::UI_BG_PATTERN})
                .add<RM::Repeat>()
                .set<RM::Scale>({5.0f, 5.0f})
                .set<TM::Position>({0, 0});

        // correction
        bgPattern->get_mut<RM::Sprite>()->repeat = true;
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
        bgPattern->set<RM::Variants>({.values{color}});
    }

public:
    struct Board {};
    struct Slot {};
    struct Gem {};
    struct Button{};
    struct IconButton{};
    struct TextButton4{};
    struct TextButton5{};
    struct TextButton6{};
    struct TextButton7{};
    struct TextButton8{};
};