#pragma once
#include "../headers/Header.h"
#include "../core/UiModule.h"
#include "Slot.h"

struct Previewer : public Entity<Previewer> {

    explicit Previewer(flecs::entity& container, int nbPreviews, const std::vector<V_COLORS>& colors, const std::vector<V_SHAPES>& shapes)
        : Entity(container.world(), "Previewer"), nbPreviews(nbPreviews), colors(colors), shapes(shapes)
    {

        this->is_a<UI::HBox>()
            .add<TM::ContainedBy>(container)
            .set<TM::Relative>({TM::Relative::Alignment::TOP_LEFT})
            .set<TM::Position, TM::Relative>({50, 50})
            .with<TM::ContainedBy>([&]{
                for (int i = 0; i < nbPreviews; i++) {
                    Slot(world(), ST_CLOSED)
                    .set<RM::Scale>({1.75, 1.75})
                    .with<TM::ContainedBy>([&]{
                        auto gem = getRandom();
                        previews.push_back(gem);
                    });
                }
            });

    }

    Gem getRandom() {
        V_COLORS color = colors[GetRandomValue(0, 100) % colors.size()];
        V_SHAPES shape = shapes[GetRandomValue(0, 100) % shapes.size()];
        return {world(), color, shape};
    }

    Gem pop() {
        auto gem = previews.front();
        auto slots = getSlots();

        previews.erase(previews.begin());
        for (int i = 0; i < slots.size() - 1; i++) {
            previews[i].setContainer(slots[i]);
        }

        slots.back().with<TM::ContainedBy>([&]{
            previews.push_back(getRandom());
        });

        return gem;
    }



private:
    int nbPreviews;
    std::vector<Gem> previews;
    std::vector<V_COLORS> colors;
    std::vector<V_SHAPES> shapes;
};