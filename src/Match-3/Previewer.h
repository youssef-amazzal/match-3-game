#pragma once
#include "../headers/Header.h"
#include "../core/UiModule.h"
#include "Slot.h"

struct Previewer : public Entity<Previewer> {

    explicit Previewer(flecs::entity& container, int nbPreviews = 0, const std::vector<V_COLORS>& colors = {}, const std::vector<V_SHAPES>& shapes = {})
        : Entity(container.world(), "Previewer"), nbPreviews(nbPreviews), colors(colors), shapes(shapes)
    {

        this->is_a<UI::HBox>()
            .add<TM::ContainedBy>(container)
            .set<TM::Relative>({TM::Relative::Alignment::TOP_LEFT})
            .set<TM::Position, TM::Relative>({50, 50})
            .with<TM::ContainedBy>([&]{
                for (int i = 0; i < nbPreviews; i++) {
                    Slot(world(), ST_CLOSED)
                    .set<RM::Scale>({1.75, 1.75});
                }
            });

    }

    Previewer& init() {
        for (int i = 0; i < nbPreviews; i++) {
            push();
        }

        return *this;
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

        push();

        return gem;
    }

    Previewer& push(Gem* gemPtr = nullptr) {
        auto index = previews.size();

        getSlots().at(index).with<TM::ContainedBy>([&]{
            Gem gem = getRandom();

            if (gemPtr) {
                gem.setColor(gemPtr->getColor());
                gem.setShape(gemPtr->getShape());
                gem.setScore({gemPtr->getScore()});
                gemPtr->destruct();
            }

            previews.push_back(gem);
        });

        return *this;
    }

    json serialize() {
        json j;
        j["nbPreviews"] = nbPreviews;

        for (auto& color : colors) {
            j["colors"].push_back(color);
        }

        for (auto& shape : shapes) {
            j["shapes"].push_back(shape);
        }

        for (auto& gem : previews) {
            j["previews"].push_back(gem.serialize());
        }

        return j;
    }

    Previewer& deserialize(json j) {
        nbPreviews = j["nbPreviews"];

        colors.clear();
        shapes.clear();
        previews.clear();

        for (auto& color : j["colors"]) {
            colors.push_back(color);
        }

        for (auto& shape : j["shapes"]) {
            shapes.push_back(shape);
        }

        for (auto& preview : j["previews"]) {
            auto gem = Gem(world()).deserialize(preview);
            push(&gem);
        }

        return *this;
    }


private:
    int nbPreviews;
    std::vector<Gem> previews;
    std::vector<V_COLORS> colors;
    std::vector<V_SHAPES> shapes;
};