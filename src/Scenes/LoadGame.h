#pragma once
#include "NewGame.h"


class LoadGame : public NewGame {

public:
    explicit LoadGame(flecs::world& world) : NewGame(world) {}

private:

    void enter() override;

};
