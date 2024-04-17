#pragma once
#include "../headers/Header.h"
#include "../core/UiModule.h"
#include "Slot.h"
#include <queue>
#include <list>

struct Previewer : public flecs::entity {


    explicit Previewer(flecs::entity& container, int nbPreviews, std::vector<V_COLORS> colors, std::vector<V_SHAPES> shapes)
        : flecs::entity(container.world()), nbPreviews(nbPreviews), colors(colors), shapes(shapes)
    {

        this->is_a<UI::HBox>()

            .add<TM::ContainedBy>(container)
            .set<TM::Relative>({TM::Relative::Alignment::TOP_CENTER})
            .set<TM::Position, TM::Relative>({0, 50})

            .set<TM::Container::Alignment>({TM::Container::Alignment::Type::COL_REV})
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

    std::vector<flecs::entity>& getSlots() {
        return this->get_mut<TM::Container::Content>()->items;
    }

    Gem getRandom() {
        V_COLORS color = colors[rand() % colors.size()];
        V_SHAPES shape = shapes[rand() % shapes.size()];
        return {world(), color, shape};
    }

    V_COLORS randomColor() {
        return colors[rand() % colors.size()];
    }

    V_SHAPES randomShape() {
        return shapes[rand() % shapes.size()];
    }


    void push() {

    }

    Gem pop() {
        auto gem = previews.front();
        auto slots = getSlots();

        previews.erase(previews.begin());
        for (int i = 0; i < slots.size() - 1; i++) {
            previews[i].setContainer(slots[i]);
        }

        slots.back().with<TM::ContainedBy>([&]{
            auto gem = getRandom();
            previews.push_back(gem);
        });

        return gem;
    }



private:
    int nbPreviews;
    std::vector<Gem> previews;
    std::vector<V_COLORS> colors;
    std::vector<V_SHAPES> shapes;


};