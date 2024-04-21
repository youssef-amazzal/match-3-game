#pragma once
#include "../headers/Header.h"

struct MatchModule {
    explicit MatchModule(flecs::world& world) {}

    //====================================//
    //              Components            //
    //====================================//

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