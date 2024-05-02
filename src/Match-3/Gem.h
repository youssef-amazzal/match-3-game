#pragma once
#include "../headers/Header.h"
#include "../core/MatchModule.h"

struct Gem : public Entity<Gem> {

    Gem(const flecs::world& world, V_COLORS color = C_GRAY, V_SHAPES shape = SH_LONG_HEX) : Entity(world, "Gem") {
        this->is_a<TM::PPhysical>()

                .set<RM::Type>({UI_ELEMENTS::UI_GEM})
                .set<RM::Variants>({{color, shape}})
                .set<RM::Scale>({2.4, 2.4})

                .set<TM::Depth>({3})
                .set<TM::Relative>({TM::Relative::Alignment::CENTER})

                .set<MM::Match>({color, shape})
                .set<MM::Score>({5});
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

    Gem& setScore(MM::Score score) {
        this->set<MM::Score>(score);
        return *this;
    }

    V_COLORS getColor() {
        return this->get<MM::Match>()->color;
    }

    V_SHAPES getShape() {
        return this->get<MM::Match>()->shape;
    }

    int getScore() {
        return this->get<MM::Score>()->score;
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

    json serialize() {
        return {
                {"color", getColor()},
                {"shape", getShape()},
                {"score", getScore()}
        };
    }

    Gem& deserialize(json j) {
        setColor(j["color"]);
        setShape(j["shape"]);
        setScore({j["score"]});
        return *this;
    }

};