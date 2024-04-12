#pragma once
#include "../headers/Header.h"

struct TransformModule {

    explicit TransformModule(flecs::world& world) {
        world.component<Position>   ("Position");
        world.component<Local>      ("Local");
        world.component<World>      ("World");
        world.component<Relative>   ("Relative");
        world.component<Area>       ("Area");
        world.component<Rotation>   ("Rotation");

        world.system<Position, Area, Position, Area, Relative, const Position>("UpdateChildPosition")
                .term_at(1).second<World>()

                // Don't : .term_at(3).second<World>().parent()
                // Do :
                .term_at(3).parent().second<World>()

                .term_at(4).parent()
                .term_at(6).second<Local>()
                .term_at(6).optional()
                .iter(updateChildPosition);
    }

    struct Position;
    struct Local;
    struct World;
    struct Relative;
    struct Area;
    struct Rotation;

private:
    //===================================//
    //             Systems               //
    //===================================//

    static void updateChildPosition(
            flecs::iter &it,
            Position *childPos, Area *childArea,
            Position *parPos,   Area *parArea,
            Relative *relative, const Position *localPos) {

        Vector2 parentCenter;

        for (auto i : it) {
            parentCenter = {parArea->width / 2.0f, parArea->height / 2.0f};

            switch (relative->alignment) {
                case Relative::Alignment::TOP_LEFT:
                    childPos[i].x = parPos->x;
                    childPos[i].y = parPos->y;
                    break;
                case Relative::Alignment::TOP_CENTER:
                    childPos[i].x = parPos->x + parentCenter.x - childArea->width / 2.0f;
                    childPos[i].y = parPos->y;
                    break;
                case Relative::Alignment::TOP_RIGHT:
                    childPos[i].x = parPos->x + parArea->width - childArea->width;
                    childPos[i].y = parPos->y;
                    break;
                case Relative::Alignment::CENTER_LEFT:
                    childPos[i].x = parPos->x;
                    childPos[i].y = parPos->y + parentCenter.y - childArea->height / 2.0f;
                    break;
                case Relative::Alignment::CENTER:
                    childPos[i].x = parPos->x + parentCenter.x - childArea->width / 2.0f;
                    childPos[i].y = parPos->y + parentCenter.y - childArea->height / 2.0f;
                    break;
                case Relative::Alignment::CENTER_RIGHT:
                    childPos[i].x = parPos->x + parArea->width - childArea->width;
                    childPos[i].y = parPos->y + parentCenter.y - childArea->height / 2.0f;
                    break;
                case Relative::Alignment::BOTTOM_LEFT:
                    childPos[i].x = parPos->x;
                    childPos[i].y = parPos->y + parArea->height - childArea->height;
                    break;
                case Relative::Alignment::BOTTOM_CENTER:
                    childPos[i].x = parPos->x + parentCenter.x - childArea->width / 2.0f;
                    childPos[i].y = parPos->y + parArea->height - childArea->height;
                    break;
                case Relative::Alignment::BOTTOM_RIGHT:
                    childPos[i].x = parPos->x + parArea->width - childArea->width;
                    childPos[i].y = parPos->y + parArea->height - childArea->height;
                    break;
            }

            if (localPos) {
                childPos[i].x += localPos[i].x;
                childPos[i].y += localPos[i].y;
            }
        }
    }

public:
    struct Position {
        float x = 0;
        float y = 0;
    };

    struct Local{};
    struct World{};

    struct Relative{
        enum class Alignment {
            TOP_LEFT,
            TOP_CENTER,
            TOP_RIGHT,

            CENTER_LEFT,
            CENTER,
            CENTER_RIGHT,

            BOTTOM_LEFT,
            BOTTOM_CENTER,
            BOTTOM_RIGHT
        };

        Alignment alignment;
    };

    struct Area {
        float width;
        float height;
    };

    struct Rotation {
        float angle;
    };
};
