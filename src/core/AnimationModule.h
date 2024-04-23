#pragma once
#include "InputModule.h"
#include "../headers/Header.h"
#include "TransformModule.h"


struct AnimationModule {
    explicit AnimationModule(flecs::world& world);

    //===================================//
    //             Components            //
    //===================================//

    struct Animation {
        struct State {
            ANIMATIONS state = ANIMATIONS::IDLE;
        };

        struct Loop {};
    };

    struct Frame {
        std::vector<int> frames{0};
        int              currentFrame = 0;
        double           frameTime    = 0;
    };

    struct Linear {
        Vector2 start    = {0, 0};
        Vector2 end      = {0, 0};
        float   duration = 0;
    };

private:
    //===================================//
    //             Systems               //
    //===================================//

    static void updateFrame(Frame& frame);
    static void updateLinear(Linear& linear, TM::Position& position);
    static void updateInteractivity(flecs::entity entity, IM::Mouse mouse);
};

using AM = AnimationModule;