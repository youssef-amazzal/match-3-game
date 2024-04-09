#pragma once
#include "Header.h"

struct Slot {
    std::string name;
    UI_ELEMENTS type;
    float x, y, width, height, rotation;
    int repeat = 1;
    bool isOccupied = false;
    bool visible;
    json properties;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Slot, name, x, y, width, height, rotation, visible)
};
