#pragma once
#include "../headers/Header.h"
#include "../core/TransformModule.h"
#include "../core/RenderModule.h"


struct Label : public flecs::entity  {

    explicit Label(flecs::entity& container, const char* text, float fontSize, float spacing) : flecs::entity(container.world()) {
        Vector2 area = MeasureTextEx(GetFontDefault(), text, fontSize, spacing);

        this->is_a<TM::PPhysical>()

                .add<TM::ContainedBy>(container)
                .set<TM::Relative>({TM::Relative::Alignment::CENTER})
                .set<TM::Depth>({3})
                .set<TM::Area>({area.x, area.y})
                .set<RM::Type>({UI_ELEMENTS::UI_BUTTON});


        this->set_name(("Label" + std::to_string(this->id())).c_str());
    }

    Label& setContainer(const flecs::entity& container) {
        this->add<TM::ContainedBy>(container);
        return *this;
    }

    Label& setColor(V_COLORS color) {
        this->set<RM::Variants>({{color}});
        return *this;
    }

};