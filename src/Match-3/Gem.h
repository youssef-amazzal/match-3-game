#pragma once
#include "../headers/Header.h"
#include "../core/UiModule.h"

struct Gem : public flecs::entity {

    struct Match {
        V_COLORS color = V_COLORS::C_GRAY;
        V_SHAPES shape = V_SHAPES::SH_DIAMOND;
    };

    Gem(const flecs::entity& container, V_COLORS color, V_SHAPES shape) : flecs::entity(container.world()) {

        this->is_a<TM::PPhysical>()

            .set<RM::Type>({UI_ELEMENTS::UI_GEM})
            .set<RM::Variants>({{color, shape}})
            .set<RM::Scale>({2.4, 2.4})

            .set<TM::Depth>({3})

            .add<TM::ContainedBy>(container)
            .set<TM::Relative>({TM::Relative::Alignment::CENTER})

            .set<Match>({color, shape});
    }

    Gem& setColor(V_COLORS color) {
        this->set<Match>({color, this->get<Match>()->shape})
                .set<RM::Variants>({{color, this->get<Match>()->shape}});
        return *this;
    }

    Gem& setShape(V_SHAPES shape) {
        this->set<Match>({this->get<Match>()->color, shape})
                .set<RM::Variants>({{this->get<Match>()->color, shape}});
        return *this;
    }

};