#pragma once
#include "../headers/Header.h"
#include "../core/UiModule.h"
#include "Slot.h"

struct Previewer : public flecs::entity {
    explicit Previewer(flecs::entity& container, int nbPreviews) : flecs::entity(container.world()) {

        this->is_a<UI::HBox>()
            .add<TM::ContainedBy>(container)
            .set<TM::Relative>({TM::Relative::Alignment::TOP_LEFT})
            .set<TM::Position, TM::Relative>({50, 50})
            .with<TM::ContainedBy>([&]{
                for (int i = 0; i < nbPreviews; i++) {
                    Slot(world(), ST_SELECTED).set<RM::Scale>({1.75, 1.75});
                }
            });
    }
};