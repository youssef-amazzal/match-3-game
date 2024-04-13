#pragma once
#include "../headers/Header.h"

struct TransformModule {

    explicit TransformModule(flecs::world& world) {
        world.component<Position>    ("Position");
        world.component<Relative>    ("Relative");
        world.component<Area>        ("Area");
        world.component<Depth>       ("Depth");
        world.component<Rotation>    ("Rotation");
        world.component<Container>   ("Container");
        world.component<ContainedBy> ("ContainedBy")
                .add(flecs::Exclusive)
                .add(flecs::OnDeleteTarget, flecs::Delete);



        world.observer("AttachToContainer")
                .with<ContainedBy>()
                .term_at(1).second(flecs::Wildcard)
                .event(flecs::OnAdd)
                .each([](flecs::entity entity) {
                    auto box = entity.target<ContainedBy>();

                    entity.child_of(box);

                    if (box) {
                        auto container = box.get_mut<Container>();
                        container->items.push_back(static_cast<const flecs::id>(entity.id()));
                    }
                });

        world.system<Container, Position, Area>().each(upddateChildPosition);

        world.system<Position, Area>().each([](flecs::entity entity, Position& pos, Area& area) {
            if (IsKeyPressed(KEY_RIGHT_ALT)) {
                std::cout << entity.name() << ": " << entity.type().str() << std::endl;
                std::printf("\n%s: pos(%.2f, %.2f), area(%.2f, %.2f)\n\n\n", entity.name().c_str(), pos.x, pos.y, area.width, area.height);
            }
        });

//        world.system<Position, Area, Position, Area, Relative, const Position>("UpdateChildPosition")
//                .term_at(3).parent()
//                .term_at(4).parent()
//                .term_at(6).second<Relative>().optional()
//
//                .with<ContainedBy>()
//                .term_at(7).second(flecs::Wildcard)
//                .term_at(7)
//
//                .iter(updateChildPosition);
    }

    struct Position;
    struct Relative;
    struct Area;
    struct Depth;
    struct Rotation;
    struct Container;
    struct ContainedBy;

private:
    //===================================//
    //             Systems               //
    //===================================//

    static void upddateChildPosition(flecs::entity parent, Container& container, Position& position, Area& area) {
        Rectangle last_element;
        float widthSum = 0, heightSum = 0;

//        std::printf("\n%s: pos(%.2f, %.2f), area(%.2f, %.2f)\n", parent.name().c_str(), position.x, position.y, area.width, area.height);
//        std::cout << std::endl;

        switch (container.alignment) {
            case Container::Alignment::ROW :
            case Container::Alignment::COL :
                last_element = {position.x, position.y, 0, 0};
                break;

            case Container::Alignment::ROW_REV :
                last_element = {position.x + area.width, position.y, 0, 0};
                break;
            case Container::Alignment::COL_REV :
                last_element = {position.x, position.y + area.height, 0, 0};
                break;

            default:
                break;
        }


        for (auto& id : container.items) {
            auto child = parent.world().entity(id);
            auto child_position = child.get_mut<Position>();
            auto child_area = child.get_mut<Area>();



            switch (container.alignment) {
                case Container::Alignment::COL:
                    child_position->y = last_element.y + last_element.height;
                    child_position->x = last_element.x;

                    last_element.height = child_area->height;
                    last_element.y = child_position->y;

                    heightSum += child_area->height;
                    widthSum   = std::max(widthSum, child_area->width);
                    break;

                case Container::Alignment::ROW:
                    child_position->x = last_element.x + last_element.width;
                    child_position->y = last_element.y;

                    last_element.width = child_area->width;
                    last_element.x = child_position->x;

                    widthSum += child_area->width;
                    heightSum = std::max(heightSum, child_area->height);
                    break;

                case Container::Alignment::COL_REV:
                    child_position->y = last_element.y - child_area->height;
                    child_position->x = last_element.x;

                    last_element.height = child_area->height;
                    last_element.y = child_position->y;

                    heightSum += child_area->height;
                    widthSum = std::max(widthSum, child_area->width);
                    break;

                case Container::Alignment::ROW_REV:
                    child_position->x = last_element.x - child_area->width;
                    child_position->y = last_element.y;

                    last_element.width = child_area->width;
                    last_element.x = child_position->x;

                    widthSum += child_area->width;
                    heightSum = std::max(heightSum, child_area->height);
                    break;

                case Container::Alignment::FREE:
                    auto child_relative     = child.get<Relative>();
                    auto child_relative_pos = child.get<Position, Relative>();
                    Vector2 center = {area.width / 2.0f, area.height / 2.0f};

                    if (child_relative) {
                        switch (child_relative->alignment) {
                            case Relative::Alignment::TOP_LEFT:
                                child_position->x = position.x;
                                child_position->y = position.y;
                                break;
                            case Relative::Alignment::TOP_CENTER:
                                child_position->x = position.x + center.x - child_area->width / 2.0f;
                                child_position->y = position.y;
                                break;
                            case Relative::Alignment::TOP_RIGHT:
                                child_position->x = position.x + area.width - child_area->width;
                                child_position->y = position.y;
                                break;
                            case Relative::Alignment::CENTER_LEFT:
                                child_position->x = position.x;
                                child_position->y = position.y + center.y - child_area->height / 2.0f;
                                break;
                            case Relative::Alignment::CENTER:
                                child_position->x = position.x + center.x - child_area->width / 2.0f;
                                child_position->y = position.y + center.y - child_area->height / 2.0f;
                                break;
                            case Relative::Alignment::CENTER_RIGHT:
                                child_position->x = position.x + area.width - child_area->width;
                                child_position->y = position.y + center.y - child_area->height / 2.0f;
                                break;
                            case Relative::Alignment::BOTTOM_LEFT:
                                child_position->x = position.x;
                                child_position->y = position.y + area.height - child_area->height;
                                break;
                            case Relative::Alignment::BOTTOM_CENTER:
                                child_position->x = position.x + center.x - child_area->width / 2.0f;
                                child_position->y = position.y + area.height - child_area->height;
                                break;
                            case Relative::Alignment::BOTTOM_RIGHT:
                                child_position->x = position.x + area.width - child_area->width;
                                child_position->y = position.y + area.height - child_area->height;
                                break;
                        }
                    }

                    if (child_relative_pos) {
                        child_position->x += child_relative_pos->x;
                        child_position->y += child_relative_pos->y;
                    }

                    break;
            }
        }

        if (!container.fixed && container.alignment != Container::Alignment::FREE) {
            area.width  = widthSum;
            area.height = heightSum;
        }
    }

//    static void updateChildPosition(
//            flecs::iter &it,
//            Position *childPos, Area *childArea,
//            Position *parPos,   Area *parArea,
//            Relative *relative, const Position *localPos) {
//
//        Vector2 parentCenter;
//
//        for (auto i : it) {
//            parentCenter = {parArea->width / 2.0f, parArea->height / 2.0f};
//
//            switch (relative->alignment) {
//                case Relative::Alignment::TOP_LEFT:
//                    childPos[i].x = parPos->x;
//                    childPos[i].y = parPos->y;
//                    break;
//                case Relative::Alignment::TOP_CENTER:
//                    childPos[i].x = parPos->x + parentCenter.x - childArea->width / 2.0f;
//                    childPos[i].y = parPos->y;
//                    break;
//                case Relative::Alignment::TOP_RIGHT:
//                    childPos[i].x = parPos->x + parArea->width - childArea->width;
//                    childPos[i].y = parPos->y;
//                    break;
//                case Relative::Alignment::CENTER_LEFT:
//                    childPos[i].x = parPos->x;
//                    childPos[i].y = parPos->y + parentCenter.y - childArea->height / 2.0f;
//                    break;
//                case Relative::Alignment::CENTER:
//                    childPos[i].x = parPos->x + parentCenter.x - childArea->width / 2.0f;
//                    childPos[i].y = parPos->y + parentCenter.y - childArea->height / 2.0f;
//                    break;
//                case Relative::Alignment::CENTER_RIGHT:
//                    childPos[i].x = parPos->x + parArea->width - childArea->width;
//                    childPos[i].y = parPos->y + parentCenter.y - childArea->height / 2.0f;
//                    break;
//                case Relative::Alignment::BOTTOM_LEFT:
//                    childPos[i].x = parPos->x;
//                    childPos[i].y = parPos->y + parArea->height - childArea->height;
//                    break;
//                case Relative::Alignment::BOTTOM_CENTER:
//                    childPos[i].x = parPos->x + parentCenter.x - childArea->width / 2.0f;
//                    childPos[i].y = parPos->y + parArea->height - childArea->height;
//                    break;
//                case Relative::Alignment::BOTTOM_RIGHT:
//                    childPos[i].x = parPos->x + parArea->width - childArea->width;
//                    childPos[i].y = parPos->y + parArea->height - childArea->height;
//                    break;
//            }
//
//
//            if (localPos) {
//                childPos[i].x += localPos[i].x;
//                childPos[i].y += localPos[i].y;
//            }
//        }
//    }

public:
    struct Position {
        float x = 0;
        float y = 0;
    };

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

    struct Container {
        enum class Alignment {FREE, COL, ROW, COL_REV, ROW_REV};

        std::vector<flecs::id> items;
        Alignment alignment = Alignment::FREE;
        bool fixed = false;
    };

//    struct Container {
//
//    };

    struct ContainedBy {
        int index;
    };

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


};
