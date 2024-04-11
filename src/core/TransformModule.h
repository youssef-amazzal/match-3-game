#pragma once
#include "../headers/Header.h"
#include "RenderModule.h"

struct TransformModule {

    explicit TransformModule(flecs::world& world) {
        world.component<Position>("Position");
        world.component<Local>("Local");
        world.component<World>("World");
        world.component<Rotation>("Rotation");

        world.system<Position, RenderModule::Sprite>()
                .term_at(1).second<World>()
                .term_at(2).optional()
                .iter(updatePosition);

        world.system<Position, RenderModule::Sprite, Position, RenderModule::Sprite, Relative, const Position>()
                .term_at(1).second<World>()

                // Don't : .term_at(3).second<World>().parent()
                // Do :
                .term_at(3).parent().second<World>()

                .term_at(4).parent()
                .term_at(6).second<Local>()
                .term_at(6).optional()
                .iter(updateChildPosition);
    }

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

        Alignment alginement;
    };

    struct Rotation {
        float angle;
    };

    static void updatePosition(flecs::iter& it, Position* worldPos, RenderModule::Sprite* sprite) {
        for (auto i : it) {
            worldPos[i].x = worldPos[i].x;
            worldPos[i].y = worldPos[i].y;

            if (sprite) {
                sprite[i].destRect.x = worldPos[i].x;
                sprite[i].destRect.y = worldPos[i].y;
            }
        }

    }

    static void updateChildPosition(
            flecs::iter &it,
            Position *worldPos, RenderModule::Sprite *sprite,
            Position *parPos,   RenderModule::Sprite *parSprite,
            Relative *relative, const Position *localPos) {

        Rectangle childDest, parentDest;
        Vector2 parentCenter;

        for (auto i : it) {
            childDest   = sprite[i].destRect;
            parentDest  = parSprite->destRect;
            parentCenter = {parentDest.width / 2.0f, parentDest.height / 2.0f};

            switch (relative->alginement) {
                case Relative::Alignment::TOP_LEFT:
                    worldPos[i].x = parPos->x;
                    worldPos[i].y = parPos->y;
                    break;
                case Relative::Alignment::TOP_CENTER:
                    worldPos[i].x = parPos->x + parentCenter.x - childDest.width / 2.0f;
                    worldPos[i].y = parPos->y;
                    break;
                case Relative::Alignment::TOP_RIGHT:
                    worldPos[i].x = parPos->x + parentDest.width - childDest.width;
                    worldPos[i].y = parPos->y;
                    break;
                case Relative::Alignment::CENTER_LEFT:
                    worldPos[i].x = parPos->x;
                    worldPos[i].y = parPos->y + parentCenter.y - childDest.height / 2.0f;
                    break;
                case Relative::Alignment::CENTER:
                    worldPos[i].x = parPos->x + parentCenter.x - childDest.width / 2.0f;
                    worldPos[i].y = parPos->y + parentCenter.y - childDest.height / 2.0f;
                    break;
                case Relative::Alignment::CENTER_RIGHT:
                    worldPos[i].x = parPos->x + parentDest.width - childDest.width;
                    worldPos[i].y = parPos->y + parentCenter.y - childDest.height / 2.0f;
                    break;
                case Relative::Alignment::BOTTOM_LEFT:
                    worldPos[i].x = parPos->x;
                    worldPos[i].y = parPos->y + parentDest.height - childDest.height;
                    break;
                case Relative::Alignment::BOTTOM_CENTER:
                    worldPos[i].x = parPos->x + parentCenter.x - childDest.width / 2.0f;
                    worldPos[i].y = parPos->y + parentDest.height - childDest.height;
                    break;
                case Relative::Alignment::BOTTOM_RIGHT:
                    worldPos[i].x = parPos->x + parentDest.width - childDest.width;
                    worldPos[i].y = parPos->y + parentDest.height - childDest.height;
                    break;
            }

            if (localPos) {
                worldPos[i].x += localPos[i].x;
                worldPos[i].y += localPos[i].y;
            }
        }
    }
};
