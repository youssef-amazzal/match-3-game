#pragma once
#include "Header.h"

using map_variants = std::unordered_map<VARIANTS, std::unordered_map<VARIANTS, int>>;
using map_animation = std::unordered_map<UI_ANIMATIONS, std::vector<int>>;

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


struct SpriteData {
    UI_ELEMENTS type;
    int id;
    float width, height;
    std::vector<std::vector<int>> vExpandTiles;
    std::vector<std::vector<int>> hExpandTiles;
    map_animation animations;
    map_variants variants;
};

struct SpriteSheet {
    Texture2D texture;
    SPRITES type;
    int rows;
    int columns;
    float scale;
    int layer;
    int frameWidth;
    int frameHeight;
    std::unordered_map<UI_ELEMENTS, SpriteData> sprites;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SpriteSheet, type, rows, columns, frameWidth, frameHeight, scale, layer)
};