#pragma once
#include "../headers/Header.h"
#include "../core/UiModule.h"
#include "Slot.h"

struct Inventory : public Entity<Inventory> {

    Inventory(flecs::entity& container, int nbItems) : Entity(container.world(), "Inventory") {
        this->is_a<UI::VBox>()
                .set<TM::Container::Gap>({5})

                .add<TM::ContainedBy>(container)
                .set<TM::Relative>({TM::Relative::Alignment::CENTER_RIGHT})
                .set<TM::Position, TM::Relative>({-30, -50})
                .with<TM::ContainedBy>([&]{
                    for (int i = 0; i < nbItems; i++) {
                        Slot(world(), ST_OPEN).set<RM::Scale>({1.75, 1.75});
                    }
                });
    }
};