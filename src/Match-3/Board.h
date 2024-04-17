#pragma once
#include "../headers/Header.h"
#include "../core/UiModule.h"
#include "Slot.h"
#include "Gem.h"


class Board : public flecs::entity {

public:
    SingleLinkedList<Gem> mainList;
    std::unordered_map <VARIANTS, DoubleLinkedList<flecs::id>> subLists;

    explicit Board(flecs::entity& container) : flecs::entity(container.world()) {

        this->is_a<UI::HBox>()
                .add<TM::ContainedBy>(container)
                .set<TM::Relative>({TM::Relative::Alignment::BOTTOM_CENTER})
                .set<TM::Position, TM::Relative>({0, -100});
    }

    Board& push_back(const Gem& newGem) {
        Slot slot = Slot(world(), ST_SELECTED);
        getSlots().push_back(slot);

        Gem gem = Gem(newGem).setContainer(slot);

        this->mainList.push_back(gem);
        subLists[gem.getColor()].push_back(gem);
        subLists[gem.getShape()].push_back(gem);

        return *this;
    }

    Board& push_front(const Gem& newGem) {
        Slot slot = Slot(world(), ST_SELECTED);
        getSlots().insert(getSlots().begin(), slot);

        Gem gem = Gem(newGem).setContainer(slot);

        this->mainList.push_front(gem);
        subLists[gem.getColor()].push_front(gem);
        subLists[gem.getShape()].push_front(gem);

        return *this;
    }

    Board& remove(int index) {
        auto current = mainList.front();
        auto color = current->data.getColor();
        auto shape = current->data.getShape();

        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        current->data.destruct();
        getSlots().at(index).destruct();
        getSlots().erase(getSlots().begin() + index);

        mainList.remove(index);
        subLists[color].remove(index);
        subLists[shape].remove(index);

        return *this;
    }

    void handleGemMatching() {
        auto current = mainList.front();
        auto colorCount = 1, shapeCount = 1;
        std::set<int> toRemove;
        bool colorMatch = false, shapeMatch = false;

        for (int index = 0; current && current->next; index++) {

            if (current->data.getColor() == current->next->data.getColor()) {
                colorCount++;
            } else {
                if (colorCount >= 3) {
                    for (int i = index - colorCount + 1; i <= index; i++) {
                        toRemove.insert(i);
                    }

                    colorMatch = true;
                }
                colorCount = 1;
            }

            if (current->data.getShape() == current->next->data.getShape()) {
                shapeCount++;
            } else {
                if (shapeCount >= 3) {
                    for (int i = index - shapeCount + 1; i <= index; i++) {
                        toRemove.insert(i);
                    }

                    shapeMatch = true;
                }
                shapeCount = 1;
            }

            current = current->next;
        }


        if (colorCount >= 3) {
            for (int i = mainList.size() - colorCount; i < mainList.size(); i++) {
                toRemove.insert(i);
            }
            colorMatch = true;
        }

        if (shapeCount >= 3) {
            for (int i = mainList.size() - shapeCount; i < mainList.size(); i++) {
                toRemove.insert(i);
            }
            shapeMatch = true;
        }

        // remember that we need to remove the items in reverse order because
        // the indexes will change in each list when we remove an item
        for (auto it = toRemove.rbegin(); it != toRemove.rend(); ++it) {
            remove(*it);
        }

        if (colorMatch) std::cout << "Color Match" << std::endl;
        if (shapeMatch) std::cout << "Shape Match" << std::endl;
    }

    void shiftLeft(VARIANTS variant) {
        auto list = subLists[variant];
        list.shiftLeft();

        auto current = mainList.front();

        for (int i = 0; current; i++ && (current = current->next)) {
            current->data.setContainer(getSlots().at(i));
        }
    }

private:
    std::vector<flecs::entity>& getSlots() {
        return this->get_mut<TM::Container::Content>()->items;
    }

};