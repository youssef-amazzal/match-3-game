#pragma once
#include "../headers/Header.h"
#include "../core/UiModule.h"
#include "Slot.h"
#include "Gem.h"

#include <unordered_map>


class Board : public flecs::entity {

public:
    SingleLinkedList<flecs::id> mainList;
    std::unordered_map <VARIANTS, DoubleLinkedList<flecs::id>> subLists;

    explicit Board(flecs::entity& container) : flecs::entity(container.world()) {

        this->is_a<UI::HBox>()
                .add<TM::ContainedBy>(container)
                .set<TM::Relative>({TM::Relative::Alignment::BOTTOM_CENTER})
                .set<TM::Position, TM::Relative>({0, -100});
//                    .with<TransformModule::ContainedBy>([&]{
//                        for (int i = 0; i < nbSlots; i++) {
//                            container.world().entity().is_a<PSlot>()
//                                .set<RM::Variants>({{ST_SELECTED}});
//                        }
//                    });

    }

    std::vector<flecs::entity>& getSlots() {
        return this->get_mut<TM::Container::Content>()->items;
    }

    Board& push_back(V_COLORS color, V_SHAPES shape) {
        Slot slot = Slot(world(), ST_SELECTED);
        getSlots().push_back(slot);

        Gem gem = Gem(slot, color, shape);

        this->mainList.push_back(gem);
        subLists[color].push_back(gem);
        subLists[shape].push_back(gem);

        return *this;
    }

    Board& push_front(V_COLORS color, V_SHAPES shape) {
        Slot slot = Slot(world(), ST_SELECTED);
        getSlots().insert(getSlots().begin(), slot);

        Gem gem = Gem(slot, color, shape);

        this->mainList.push_front(gem);
        subLists[color].push_front(gem);
        subLists[shape].push_front(gem);

        return *this;
    }

};