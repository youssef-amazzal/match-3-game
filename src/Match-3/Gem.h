#pragma once
#include "../headers/Header.h"
#include "../core/UiModule.h"

struct Gem : public flecs::entity {


    struct Match {
        V_COLORS color = V_COLORS::C_GRAY;
        V_SHAPES shape = V_SHAPES::SH_DIAMOND;
    };

    Gem(const flecs::world& world, const flecs::id id) : flecs::entity(world, id) {};
    Gem(const flecs::world& world, const flecs::entity entity) : flecs::entity(world, entity) {}

    Gem(const Gem& gem) : flecs::entity(gem) {}

    Gem(const flecs::world& world, V_COLORS color, V_SHAPES shape) : flecs::entity(world) {
        this->is_a<TM::PPhysical>()

                .set<RM::Type>({UI_ELEMENTS::UI_GEM})
                .set<RM::Variants>({{color, shape}})
                .set<RM::Scale>({2.4, 2.4})

                .set<TM::Depth>({3})
                .set<TM::Relative>({TM::Relative::Alignment::CENTER})

                .set<Match>({color, shape});

        this->set_name(("Gem" + std::to_string(this->id())).c_str());
    }


    Gem(const flecs::entity& container, V_COLORS color, V_SHAPES shape) : Gem(container.world(), color, shape) {
        this->add<TM::ContainedBy>(container);
    }

    Gem& setContainer(const flecs::entity& container) {
        this->add<TM::ContainedBy>(container);
        return *this;
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

    V_COLORS getColor() {
        return this->get<Match>()->color;
    }

    V_SHAPES getShape() {
        return this->get<Match>()->shape;
    }

};