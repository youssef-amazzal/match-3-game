#pragma once
#include "../headers/Header.h"
#include "TransformModule.h"
#include "RenderModule.h"
#include "UiModule.h"

struct MatchModule {

    explicit MatchModule(flecs::world& world) {
        world.import<TransformModule>();
        world.import<RenderModule>();

    }

private:


public:
    struct Score {
        int score = 10;
    };
};

using MM = MatchModule;