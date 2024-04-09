#pragma once
#include "Header.h"
#include "../utils/ResourceManager.h"

struct Position {
    float x, y;
};

struct Match {
    V_COLORS color;
    V_SHAPES shape;
};

//struct RenderOld {
//    SPRITES_SHEETS sheetId = SPRITES_SHEETS::SP_INVALID;
//    UI_ELEMENTS type = UI_ELEMENTS::UI_INVALID;
//    Rectangle sourceRect = {0, 0, TILE_SIZE, TILE_SIZE};
//    float xScale = 1;
//    float yScale = 1;
//    int zOrder = 0;
//
//    RenderOld() = default;
//
//    template<typename... Variants>
//    explicit RenderOld(UI_ELEMENTS type, Variants... variant) : type(type) {
//        auto ElementData = RSC::sprites[type];
//
//        sheetId     = ElementData.source;
//        sourceRect  = ElementData.sourceRect(variant...);
//
//
//
//    }
//};

