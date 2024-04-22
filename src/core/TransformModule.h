#pragma once
#include "../headers/Header.h"

struct TransformModule {

    explicit TransformModule(flecs::world& world);

    //===================================//
    //            Components             //
    //===================================//
    struct Position {
        float x = 0;
        float y = 0;
    };

    struct Relative{
        enum class Alignment {
            TOP_LEFT,       TOP_CENTER,     TOP_RIGHT,
            
            CENTER_LEFT,    CENTER,         CENTER_RIGHT,
            
            BOTTOM_LEFT,    BOTTOM_CENTER,  BOTTOM_RIGHT
        };

        Alignment alignment = Alignment::TOP_LEFT;
    };

    struct Container {
        struct Content {
            std::vector<flecs::entity> items;
        };
        
        struct Alignment {
            enum class Type {
                FREE, COL, ROW, COL_REV, ROW_REV
            };
            Type type = Type::FREE;
        };
        
        struct Fixed {};
        
        struct Gap {
            float value = 0;
        };
    };

    struct ContainedBy {};

    struct Area {
        float width;
        float height;
    };

    struct Depth {
        int value = 0;
    };

    struct Rotation {
        float angle;
    };

    //===================================//
    //              Prefabs              //
    //===================================//
    struct PPhysical {};


private:
    //===================================//
    //            Observers              //
    //===================================//

    static void onAddContainedBy(flecs::entity entity);
    static void onRemoveContainedBy(flecs::entity entity);

    //===================================//
    //             Systems               //
    //===================================//

    static void updateChildPosition(flecs::entity parent);
};

using TM = TransformModule;