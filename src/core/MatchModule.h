#pragma once
#include "../headers/Header.h"
#include "TransformModule.h"
#include "RenderModule.h"
#include "UiModule.h"
#include "../core/UiModule.h"

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

    struct Match {
        V_COLORS color = C_GRAY;
        V_SHAPES shape = SH_DIAMOND;
    };

    struct Multiplier {
        int value = 1;
        int duration = 0;
    };

};

using MM = MatchModule;