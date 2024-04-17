#pragma once
#include "../headers/Header.h"
#include "../core/UiModule.h"
#include "Slot.h"
#include "Gem.h"


class Board : public flecs::entity {

public:
    SingleLinkedList<Gem> mainList;
    std::unordered_map <VARIANTS, DoubleLinkedList<Gem>> subLists;

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

        printLists(gem.getColor(), gem.getShape());


        return *this;
    }

    Board& remove(int index) {
        auto current = mainList.front();

        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        auto color = current->data.getColor();
        auto shape = current->data.getShape();

        auto gem = Gem(current->data);

        std::cout << "\nBefore removing" << std::endl;
        printLists(color, shape);

        mainList.remove(gem);
        subLists[color].remove(gem);
        subLists[shape].remove(gem);

        std::cout << "\nAfter removing" << std::endl;
        printLists(color, shape);

        gem.destruct();
        getSlots().at(index).destruct();
        getSlots().erase(getSlots().begin() + index);

        return *this;
    }

    void printList(const std::string& listName, DoubleLinkedList<Gem>& list) {
        std::printf("%s: ", listName.c_str());
        auto pNode = list.front();
        while (pNode && pNode->next != list.front()) {
            std::printf("%s, ", pNode->data.toString().c_str());
            pNode = pNode->next;
        }
        if (pNode) std::printf("%s, ", pNode->data.toString().c_str());
        std::cout << std::endl;
    }

    void printLists(V_COLORS color, V_SHAPES shape) {
        printList("Color list", subLists[color]);
        printList("Shape list", subLists[shape]);
        std::cout << std::endl;
    }

    void printLists(V_COLORS color) {
        printList("Color list", subLists[color]);
        printList("DIAMOND list", subLists[SH_DIAMOND]);
        printList("TRIANGLE list", subLists[SH_TRIANGLE]);
        printList("ROUND list", subLists[SH_ROUND]);
        printList("KITE list", subLists[SH_KITE]);
        std::cout << std::endl;
    }

    void handleGemMatching() {
        auto current = mainList.front();
        auto colorCount = 1, shapeCount = 1;
        std::set<int> toRemove;
        bool colorMatch = false, shapeMatch = false;

        for (int index = 0; current && current->next != mainList.front(); index++) {

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