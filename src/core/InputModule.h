#pragma once
#include "../headers/Header.h"
#include "TransformModule.h"

struct InputModule {

    explicit InputModule(flecs::world& world) {
        world.system<Mouse, TM::Position, TM::Area>()
            .kind(flecs::OnLoad)
            .each(updateMouseData);
    }

    struct Mouse {
        bool isHovered      = false;
        bool isLeftPressed  = false;
        bool isRightPressed = false;
    };

    struct Keyboard{};

private:
    static void updateMouseData(flecs::entity entity, Mouse& mouse, const TM::Position& position, const TM::Area& area) {
        Vector2 curPos = GetMousePosition();

        mouse = {false, false, false};

        if (
            curPos.x >= position.x && curPos.x <= position.x + area.width &&
            curPos.y >= position.y && curPos.y <= position.y + area.height
        ) {
            mouse.isHovered = true;
            std::cout << entity.name() << std::endl;
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) mouse.isLeftPressed   = true;
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) mouse.isRightPressed = true;
        }

    }
};

using IM = InputModule;