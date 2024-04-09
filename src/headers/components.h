#pragma once
#include "Header.h"

struct Position {
    float x, y;
};

struct Match {
    V_COLORS color;
    V_SHAPES shape;
};

struct Renderable {
    SPRITES spritesheetID;
    Rectangle sourceRect;
    float xScale;
    float yScale;
    int zOrder;

    Renderable() : spritesheetID(SPRITES::SP_INVALID), sourceRect({0, 0, 0, 0}), xScale(1), yScale(1), zOrder(0) {}
};

