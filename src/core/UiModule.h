#pragma once
#include "../headers/Header.h"
#include "RenderModule.h"
#include "TransformModule.h"
#include "InputModule.h"



struct UiModule {

    explicit UiModule(flecs::world& world) {
        // Prefabs
        world.prefab<HBox>("P:HBox").is_a<TM::PPhysical>()
                .set_override<TM::Depth>({1})
                .add<TM::Container>()
                .set<TM::Container::Alignment>({TM::Container::Alignment::Type::ROW})
                .set<RM ::Repeat>({RM::Repeat::HORIZONTAL});

        world.prefab<VBox>("P:VBox").is_a<TM::PPhysical>()
                .set_override<TM::Depth>({1})
                .add<TM::Container>()
                .set<TM::Container::Alignment>({TM::Container::Alignment::Type::COL})
                .set<RM ::Repeat>({RM::Repeat::VERTICAL});
    }

    struct HBox {};
    struct VBox {};

};

using UI = UiModule;