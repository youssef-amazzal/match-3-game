#pragma once
#include "../headers/Header.h"
#include "../core/UiModule.h"

struct Slot : public flecs::entity {

    explicit Slot(const flecs::world& world, VARIANTS variant) : flecs::entity(world) {

        this->is_a<TM::PPhysical>()

            .set<RM::Type>({UI_ELEMENTS::UI_GEM_SLOT})
            .set<RM::Variants>({{variant}})
            .set<RM::Scale>({1.5, 1.5})

            .set<TM::Depth>({2});

    }
};