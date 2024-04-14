#pragma once
#include "../headers/Header.h"
#include "RenderModule.h"
#include "TransformModule.h"
#include "InputModule.h"



struct UiModule {

    explicit UiModule(flecs::world& world) {
        // Prefabs
        world.prefab<PPhysical>("P:Physical")
                .set_override<TM::Position>({0, 0})
                .set_override<TM::Area>({0, 0})
                .set_override<TM::Depth>({1});

        world.prefab<HBox>("P:HBox").is_a<PPhysical>()
                .set_override<TM::Depth>({1})
                .add<TM::Container>()
                .set<TM::Container::Alignment>({TM::Container::Alignment::Type::ROW})
                .set<RM ::Repeat>({RM::Repeat::HORIZONTAL});

        world.prefab<VBox>("P:VBox").is_a<PPhysical>()
                .set_override<TM::Depth>({1})
                .add<TM::Container>()
                .set<TM::Container::Alignment>({TM::Container::Alignment::Type::COL})
                .set<RM ::Repeat>({RM::Repeat::VERTICAL});

        world.prefab<PSlot>("P:PSlot").is_a<PPhysical>()

                .set<RM::Type>({UI_ELEMENTS::UI_GEM_SLOT})
                .set_override<RM::Scale>({1.3, 1.3})
                .set<TM::Depth>({2})

                .set_override<TM::Position>({100, 100});


        world.prefab<PGem>("P:Gem").is_a<PPhysical>()

                .set<RM::Type>({UI_ELEMENTS::UI_GEM})
                .set<RM::Scale>({2, 2})
                .set<TM::Depth>({3})

                .set<TM::Relative>({TM::Relative::Alignment::CENTER});


    }

    struct HBox {};
    struct VBox {};
    struct PSlot {};
    struct PGem {};
    struct PButton{};
    struct PIconButton{};
    struct PTextButton4{};
    struct PTextButton5{};
    struct PTextButton6{};
    struct PTextButton7{};
    struct PTextButton8{};

private:
    struct PPhysical {};
};

using UI = UiModule;