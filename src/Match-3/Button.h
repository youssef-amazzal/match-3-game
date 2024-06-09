#pragma once
#include "Entity.h"
#include "Label.h"
#include "../core/InputModule.h"

struct Button : public Entity<Button>  {

    explicit Button(flecs::entity& container,UI_ELEMENTS type,  std::vector<VARIANTS> variants = {C_GREEN}) : Button(container, 1, type, std::move(variants)) {};
    explicit Button(flecs::entity& container, const int expansion = 1, UI_ELEMENTS type = UI_BUTTON,  std::vector<VARIANTS> variants = {C_GREEN})
        : Entity(container.world(), "Button") {

        this->is_a<TM::PPhysical>()

                .set<RM::Sprite::Key>({type})
                .set<RM::Variants>({std::move(variants)})
                .set<RM::Expandable>({expansion, 1})
                .set<RM::Scale>({3, 3})

                .set<IM::Mouse>({false, false, false})

                .add<TM::ContainedBy>(container)
                .set<TM::Relative>({TM::Relative::Alignment::CENTER})

                .set<TM::Depth>({3});
    }

    Button& setLabel(const std::string& text, float fontSize = 40, float spacing = 5) {
        Label(*this, text, fontSize, spacing);
        return *this;
    }

    Button& setVariant(const std::vector<VARIANTS>& variants) {
        this->set<RM::Variants>({variants});
        return *this;
    }

    bool isPressed() const {
        return this->has<IM::Mouse>() && this->get<IM::Mouse>()->isLeftPressed || this->get<IM::Mouse>()->isRightPressed;
    }

    bool isHovered() const {
        return this->has<IM::Mouse>() && this->get<IM::Mouse>()->isHovered;
    }

    bool isClicked() const {
        return this->has<IM::Mouse>() && (this->get<IM::Mouse>()->isLeftReleased || this->get<IM::Mouse>()->isRightReleased);
    }

    Button& desactivate() {
        this
            ->remove<IM::Mouse>()
            .set<AM::Animation::State>({ANIMATIONS::PRESS});

        return *this;
    }

    Button& activate() {
        this
            ->set<IM::Mouse>({false, false, false})
            .set<AM::Animation::State>({ANIMATIONS::IDLE});

        return *this;
    }
};
