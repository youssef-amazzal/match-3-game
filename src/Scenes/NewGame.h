#pragma once
#include "Scene.h"
#include "../core/MatchModule.h"
#include "../Match-3/Background.h"
#include "../Match-3/Board.h"
#include "../Match-3/Previewer.h"
#include "../Match-3/Inventory.h"
#include "../Match-3/Label.h"

class NewGame : public Scene {
    Background* background = nullptr;
    Board*      board      = nullptr;
    Inventory*  inventory  = nullptr;
    Previewer*  previewer  = nullptr;
    Label*      scoreLabel = nullptr;
    int score = 0;

public:
    explicit NewGame(flecs::world& world) : Scene(world) {}

    ~NewGame() override {
        delete background;
        delete board;
        delete inventory;
        delete previewer;
        delete scoreLabel;
    }

private:

    void enter() override;

    Scene* update() override;

    void exit() override;

    json serialize() {
        json j;

        j["Board"] = board->serialize();
        j["Previewer"] = previewer->serialize();
        j["Score"] = score;

        return j;
    }

    NewGame& deserialze(json j) {
        board->deserialize(j["Board"]);
        previewer->deserialize(j["Previewer"]);
        score = j["Score"];
        return *this;
    }

};
