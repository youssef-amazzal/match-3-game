#pragma once
#include "../headers/Header.h"
#include "../core/UiModule.h"
#include "../core/MatchModule.h"

struct Gem : public flecs::entity {

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

                .set<MM::Match>({color, shape});

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
        this->set<MM::Match>({color, this->get<MM::Match>()->shape})
                .set<RM::Variants>({{color, this->get<MM::Match>()->shape}});
        return *this;
    }

    Gem& setShape(V_SHAPES shape) {
        this->set<MM::Match>({this->get<MM::Match>()->color, shape})
                .set<RM::Variants>({{this->get<MM::Match>()->color, shape}});
        return *this;
    }

    V_COLORS getColor() {
        return this->get<MM::Match>()->color;
    }

    V_SHAPES getShape() {
        return this->get<MM::Match>()->shape;
    }

    bool operator==(const Gem& gem) {
        return this->id() == gem.id();
    }

    auto toString() {
        std::string color, shape;

        switch (getColor()) {
            case C_RED:
                color = "Red(" + std::to_string(getColor()) + ")";
                break;
            case C_BLUE:
                color = "Blue(" + std::to_string(getColor()) + ")";
                break;
            case C_GREEN:
                color = "Green(" + std::to_string(getColor()) + ")";
                break;
            case C_YELLOW:
                color = "Yellow(" + std::to_string(getColor()) + ")";
                break;
        }

        switch (getShape()) {
            case SH_DIAMOND:
                shape = "Diamond(" + std::to_string(getShape()) + ")";
                break;
            case SH_KITE:
                shape = "Kite(" + std::to_string(getShape()) + ")";
                break;
            case SH_ROUND:
                shape = "Round(" + std::to_string(getShape()) + ")";
                break;
            case SH_TRIANGLE:
                shape = "Triangle(" + std::to_string(getShape()) + ")";
                break;
        }

        return std::string("(" + color + ", " + shape + ")");
    }

};