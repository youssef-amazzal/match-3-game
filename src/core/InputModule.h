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
        bool isLeftReleased = false;
        bool isRightReleased = false;
    };

    struct Keyboard{};

private:
    static void updateMouseData(flecs::entity entity, Mouse& mouse, const TM::Position& position, const TM::Area& area) {
        Vector2 curPos = GetMousePosition();
        mouse = {false, false, false, false, false};

        if (
            curPos.x >= position.x && curPos.x <= position.x + area.width &&
            curPos.y >= position.y && curPos.y <= position.y + area.height
        ) {
            mouse.isHovered = true;

            mouse.isLeftPressed = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
            mouse.isRightPressed = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
            mouse.isLeftReleased = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
            mouse.isRightReleased = IsMouseButtonReleased(MOUSE_BUTTON_RIGHT);

        }
    }
};

using IM = InputModule;