#pragma once
#include "Label.h"
#include "../core/InputModule.h"

struct Button : public flecs::entity  {

    explicit Button(entity& container, const char* text, const int width, const RM::Scale scale, V_COLORS color = C_GREEN) : entity(container.world()) {

        this->is_a<TM::PPhysical>()

                .set<RM::Type>({UI_BUTTON})
                .set<RM::Variants>({{color}})
                .set<RM::Expandable>({width, 1})
                .set<RM::Scale>(scale)

                .add<IM::Mouse>()

                .add<TM::ContainedBy>(container)
                .set<TM::Relative>({TM::Relative::Alignment::CENTER})
                // .set<TM::Position, TM::Relative>({0, -100})

                .set<TM::Depth>({3});

        Label(container, text, 20, 5).setContainer(*this);

        this->set_name(("Button" + std::to_string(this->id())).c_str());
    }

    explicit Button(flecs::entity& container, UI_ELEMENTS type, std::vector<VARIANTS> variants, RM::Scale scale) : flecs::entity(container.world()) {
        this->is_a<TM::PPhysical>()

                .set<RM::Type>({type})
                .set<RM::Variants>({std::move(variants)})
                .set<RM::Scale>(scale)

                .add<IM::Mouse>()

                .add<TM::ContainedBy>(container)
                .set<TM::Relative>({TM::Relative::Alignment::CENTER})
                // .set<TM::Position, TM::Relative>({0, -100})

                .set<TM::Depth>({3});

        this->set_name(("Button" + std::to_string(this->id())).c_str());
    }

    explicit Button(flecs::entity& container, RM::Scale scale,  V_COLORS color = C_GREEN) : flecs::entity(container.world()) {
        this->is_a<TM::PPhysical>()
                .set<RM::Type>({UI_ELEMENTS::UI_BUTTON})
                .set<RM::Variants>({{color}})
                .set<RM::Scale>({2.4, 2.4})

                .add<TM::ContainedBy>(container)
                .set<TM::Relative>({TM::Relative::Alignment::CENTER})
                // .set<TM::Position, TM::Relative>({0, -100})

                .set<TM::Depth>({3});


        this->set_name(("Button" + std::to_string(this->id())).c_str());
    }

    Button& setContainer(const flecs::entity& container) {
        this->add<TM::ContainedBy>(container);
        return *this;
    }

    Button& setColor(V_COLORS color) {
        this->set<RM::Variants>({{color}});
        return *this;
    }

    Button& press() {
        this->set<AM::Animation::State>({ANIMATIONS::PRESS});
        return *this;
    }

    Button& idle() {
        this->set<AM::Animation::State>({ANIMATIONS::IDLE});
        return *this;
    }
};
