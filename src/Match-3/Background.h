#pragma once
#include "Entity.h"
#include "../headers/Header.h"
#include "../core/TransformModule.h"
#include "../core/RenderModule.h"

struct Background : public Entity<Background> {

    explicit Background(entity& container, V_COLORS color) : Entity(container.world(), "Background") {

        this->is_a<TM::PPhysical>()
            .add<TM::ContainedBy>(container)
            .set<RM::Sprite::Key>({UI_BG_PATTERN})
            .set<RM::Variants>({{color}})
            .add<RM::Repeat>()

            .set<TM::Area>({SCREEN_WIDTH + 100, SCREEN_HEIGHT + 100})
            .add<TM::Container::Fixed>()
            .set<TM::Depth>({})

            .set<AM::Linear, AM::Animation>({
                .start = {-64, -64},
                .end = {0, 0},
                .duration = 1.5,
            });
    }

};