#include "TransformModule.h"

TM::TransformModule(flecs::world& world) {
    // Components
    world.component<ContainedBy>()
            .add(flecs::Exclusive)
            .add(flecs::OnDeleteTarget, flecs::Delete);

    auto Alignment = world.component<Container::Alignment>();
    auto Content = world.component<Container::Content>();
    auto Gap = world.component<Container::Gap>();

    world.component<Container>()
            .add(flecs::With, Content)
            .add(flecs::With, Alignment)
            .add(flecs::With, Gap);

    // Prefabs
    world.prefab<PPhysical>("P:Physical")
            .set_override<Position>({0, 0})
            .set_override<Area>({0, 0})
            .set_override<Depth>({1});


    // Observers
    world.observer("OnAdd:ContainedBy")
            .with<ContainedBy>()
            .term_at(1).second(flecs::Wildcard)
            .event(flecs::OnAdd)
            .each(onAddContainedBy);

    world.observer("OnRemove:ContainedBy")
            .with<ContainedBy>()
            .term_at(1).second(flecs::Wildcard)
            .event(flecs::OnRemove)
            .each(onRemoveContainedBy);

    // Systems
    world.system("UpdateChildPosition").with<Container>().each(updateChildPosition);

    world.system<Position, Area>("PrintEntities").each([](flecs::entity entity, Position& pos, Area& area) {
        if (IsKeyPressed(KEY_RIGHT_ALT)) {
            std::cout << entity.name() << ": " << entity.type().str() << std::endl;
            std::printf("\n%s: pos(%.2f, %.2f), area(%.2f, %.2f)\n\n\n", entity.name().c_str(), pos.x, pos.y, area.width, area.height);
        }
    });
}

//===================================//
//             Observers             //
//===================================//

void TM::onAddContainedBy(flecs::entity entity) {
    auto box = entity.target<ContainedBy>();

    entity.child_of(box);

    if (box) {
        auto content = box.add<Container>().get_mut<Container::Content>();
        content->items.push_back(entity);
    }
}

void TM::onRemoveContainedBy(flecs::entity entity) {
    auto box = entity.target<ContainedBy>();

    entity.remove(flecs::ChildOf, box);

    if (box) {
        auto content = box.get_mut<Container::Content>();
        auto it = std::find(content->items.begin(), content->items.end(), entity);
        if (it != content->items.end()) {
            content->items.erase(it);
        }
    }
}



//===================================//
//             Systems               //
//===================================//

void TM::updateChildPosition(flecs::entity parent) {
    Rectangle last_element;
    float widthSum = 0, heightSum = 0;

    Container::Content*         content     = parent.get_mut<Container::Content>();
    const Container::Alignment* alignment   = parent.get<Container::Alignment>();
    const Container::Gap*       gap         = parent.get<Container::Gap>();
    bool                        fixed       = parent.has<Container::Fixed>();
    Position*                   position    = parent.get_mut<Position>();
    Area*                       area        = parent.get_mut<Area>();



    switch (alignment->type) {
        case Container::Alignment::Type::ROW :
        case Container::Alignment::Type::COL :
            last_element = {position->x, position->y, 0, 0};
            break;

        case Container::Alignment::Type::ROW_REV :
            last_element = {position->x + area->width, position->y, 0, 0};
            break;
        case Container::Alignment::Type::COL_REV :
            last_element = {position->x, position->y + area->height, 0, 0};
            break;

        default:
            break;
    }


    for (auto& id : content->items) {
        auto child = parent.world().entity(id);
        auto child_position = child.get_mut<Position>();
        auto child_area = child.get_mut<Area>();

        switch (alignment->type) {
            case Container::Alignment::Type::COL:
                child_position->y = last_element.y + last_element.height + gap->value;
                child_position->x = last_element.x;

                last_element.height = child_area->height;
                last_element.y = child_position->y;

                heightSum += child_area->height + gap->value;
                widthSum   = std::max(widthSum, child_area->width);
                break;

            case Container::Alignment::Type::ROW:
                child_position->x = last_element.x + last_element.width + gap->value;
                child_position->y = last_element.y;

                last_element.width = child_area->width;
                last_element.x = child_position->x;

                widthSum += child_area->width + gap->value;
                heightSum = std::max(heightSum, child_area->height);
                break;

            case Container::Alignment::Type::COL_REV:
                child_position->y = last_element.y - child_area->height - gap->value;
                child_position->x = last_element.x;

                last_element.height = child_area->height;
                last_element.y = child_position->y;

                heightSum += child_area->height + gap->value;
                widthSum = std::max(widthSum, child_area->width);
                break;

            case Container::Alignment::Type::ROW_REV:
                child_position->x = last_element.x - child_area->width - gap->value;
                child_position->y = last_element.y;

                last_element.width = child_area->width;
                last_element.x = child_position->x;

                widthSum += child_area->width + gap->value;
                heightSum = std::max(heightSum, child_area->height);
                break;

            case Container::Alignment::Type::FREE:
                auto child_relative     = child.get<Relative>();
                auto child_relative_pos = child.get<Position, Relative>();
                Vector2 center = {area->width / 2.0f, area->height / 2.0f};

                if (child_relative) {
                    switch (child_relative->alignment) {
                        case Relative::Alignment::TOP_LEFT:
                            child_position->x = position->x;
                            child_position->y = position->y;
                            break;
                        case Relative::Alignment::TOP_CENTER:
                            child_position->x = position->x + center.x - child_area->width / 2.0f;
                            child_position->y = position->y;
                            break;
                        case Relative::Alignment::TOP_RIGHT:
                            child_position->x = position->x + area->width - child_area->width;
                            child_position->y = position->y;
                            break;
                        case Relative::Alignment::CENTER_LEFT:
                            child_position->x = position->x;
                            child_position->y = position->y + center.y - child_area->height / 2.0f;
                            break;
                        case Relative::Alignment::CENTER:
                            child_position->x = position->x + center.x - child_area->width / 2.0f;
                            child_position->y = position->y + center.y - child_area->height / 2.0f;
                            break;
                        case Relative::Alignment::CENTER_RIGHT:
                            child_position->x = position->x + area->width - child_area->width;
                            child_position->y = position->y + center.y - child_area->height / 2.0f;
                            break;
                        case Relative::Alignment::BOTTOM_LEFT:
                            child_position->x = position->x;
                            child_position->y = position->y + area->height - child_area->height;
                            break;
                        case Relative::Alignment::BOTTOM_CENTER:
                            child_position->x = position->x + center.x - child_area->width / 2.0f;
                            child_position->y = position->y + area->height - child_area->height;
                            break;
                        case Relative::Alignment::BOTTOM_RIGHT:
                            child_position->x = position->x + area->width - child_area->width;
                            child_position->y = position->y + area->height - child_area->height;
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

    if (!fixed && alignment->type != Container::Alignment::Type::FREE) {
        area->width  = widthSum;
        area->height = heightSum;
    }
}