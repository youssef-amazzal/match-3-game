#pragma once
#include "../headers/Header.h"
#include "../core/UiModule.h"

struct Slot : public flecs::entity {

    Slot(const flecs::world& world, const flecs::id id) : flecs::entity(world, id) {}
    Slot(const flecs::world& world, const flecs::entity entity) : flecs::entity(world, entity) {}

    Slot(const Slot& slot) : flecs::entity(slot) {}

    explicit Slot(const flecs::world& world, VARIANTS variant) : flecs::entity(world) {

        this->is_a<TM::PPhysical>()

            .set<RM::Type>({UI_ELEMENTS::UI_GEM_SLOT})
            .set<RM::Variants>({{variant}})
            .set<RM::Scale>({1.5, 1.5})

            .set<TM::Depth>({2});

        this->set_name(("Slot" + std::to_string(this->id())).c_str());
    }
};