#pragma once
#include "../headers/Header.h"

struct Background : public flecs::entity {

    explicit Background(flecs::entity& container, V_COLORS color) : flecs::entity(container.world()) {

        this->is_a<TM::PPhysical>()
            .add<TM::ContainedBy>(container)
            .set<RM::Type>({UI_BG_PATTERN})
            .add<RM::Repeat>()

            .set<TM::Area>({SCREEN_WIDTH + 100, SCREEN_HEIGHT + 100})
            .add<TM::Container::Fixed>()
            .set<TM::Depth>({})

            .set<AM::Linear, AM::Animation>({
                .start = {-64, -64},
                .end = {0, 0},
                .duration = 1.5,
            });

        this->set_name(("Background" + std::to_string(this->id())).c_str());
    }

};