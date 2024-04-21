#pragma once

struct Button : public flecs::entity  {

    explicit Button(flecs::entity& container, V_COLORS color = C_GREEN) : flecs::entity(container.world()) {
        this->is_a<TM::PPhysical>()

                .add<TM::ContainedBy>(container)
                .set<TM::Relative>({TM::Relative::Alignment::CENTER})
                // .set<TM::Position, TM::Relative>({0, -100})

                .set<TM::Depth>({3})

                .set<RM::Type>({UI_ELEMENTS::UI_BUTTON})
                .set<RM::Variants>({{color}})
                .set<RM::Scale>({2.4, 2.4});


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