#pragma once
#include "Entity.h"
#include "../headers/Header.h"
#include "../core/UiModule.h"
#include "Slot.h"
#include "Gem.h"
#include "LinkedList.h"


class Board : public Entity<Board> {

public:
    GemList mainList;

    explicit Board(flecs::entity& container) : Entity(container.world(), "Board") {

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

        return *this;
    }

    Board& push_front(const Gem& newGem) {
        Slot slot = Slot(world(), ST_SELECTED);
        getSlots().insert(getSlots().begin(), slot);

        Gem gem = Gem(newGem).setContainer(slot);

        this->mainList.push_front(gem);

        return *this;
    }

    Board& remove(int index) {

        mainList.remove(index);

        getSlots().at(index).destruct();
        getSlots().erase(getSlots().begin() + index);

        return *this;
    }

    void handleGemMatching() {
        if (mainList.size() < 3) return;

        auto current = mainList.front();
        auto colorCount = 1, shapeCount = 1;
        std::set<int> toRemove;
        bool colorMatch = false, shapeMatch = false;

        for (int index = 0; current && current->next != mainList.front(); index++) {

            if (current->gem.getColor() == current->next->gem.getColor()) {
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

            if (current->gem.getShape() == current->next->gem.getShape()) {
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

    void shiftColorLeft(V_COLORS color) {
        if (mainList.size() < 2) return;
        mainList.shiftColorLeft(color);
    }

    void shiftShapeLeft(V_SHAPES shape) {
        if (mainList.size() < 2) return;
        mainList.shiftShapeLeft(shape);
    }
};