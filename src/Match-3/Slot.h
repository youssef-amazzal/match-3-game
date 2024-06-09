#pragma once
#include "../headers/Header.h"

struct Slot : public Entity<Slot> {

    explicit Slot(const flecs::world& world, VARIANTS variant) : Entity(world, "Slot") {

        this->is_a<TM::PPhysical>()

            .set<RM::Sprite::Key>({UI_ELEMENTS::UI_GEM_SLOT})
            .set<RM::Variants>({{variant}})
            .set<RM::Scale>({1.5, 1.5})

            .set<TM::Depth>({2});
    }
};