#pragma once
#include "../headers/Header.h"
#include "../core/TransformModule.h"
#include "../core/RenderModule.h"


struct Label : public Entity<Label>  {

    explicit Label(flecs::entity& container, std::string text, float fontSize, float spacing) : Entity(container.world(), "Label") {

        this->is_a<TM::PPhysical>()
                .add<TM::ContainedBy>(container)
                .set<TM::Relative>({TM::Relative::Alignment::CENTER})
                .set<TM::Depth>({3})
                .set<RM::Text>({text, fontSize, spacing});
    }

    Label& setColor(V_COLORS color) {
        this->set<RM::Variants>({{color}});
        return *this;
    }

    Label& setText(std::string text) {
        const auto txtComponent = this->get_mut<RM::Text>();
        this->set<RM::Text>({text, txtComponent->fontSize, txtComponent->spacing});
        return *this;
    }

    json serialize() {
        json j;
        j["text"] = this->get<RM::Text>()->text;
        j["color"] = this->get<RM::Variants>()->values[0];
        return j;
    }

    Label& deserialize(json j) {
        this->setText(j["text"]);
        this->setColor(j["color"]);
        return *this;
    }
};
