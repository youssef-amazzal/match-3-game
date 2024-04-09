#pragma once
#include "../headers/Header.h"


struct SpriteData;
struct SpriteSheet;

class ResourceManager {
private:
    ResourceManager() = default;
    static void loadSpriteSheets();
    static void loadSprites();

public:
    static std::unordered_map<SPRITES_SHEETS, std::shared_ptr<SpriteSheet>> spriteSheets;
    static std::unordered_map<UI_ELEMENTS, SpriteData> sprites;

    static void loadTextures();
    static void loadAudio();
    static void loadFonts();

private:
    static void loadIndividualSprites(const json& item, SPRITES_SHEETS sheetType);
    static void loadAnimations(const json& sprite, SpriteData& data);
    static void loadExpansions(const json& sprite, SpriteData& data);
    static void loadVariants(const json& sprite, SpriteData& data);

};

using RSC = ResourceManager;

//===================== Complementary Structures =====================

struct SpriteSheet {
    Texture2D       texture;
    SPRITES_SHEETS  type;
    int             rows;
    int             columns;
    float           scale;
    int             layer;
    float           tileWidth;
    float           tileHeight;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SpriteSheet, type, rows, columns, tileWidth, tileHeight, scale, layer)

};

using ExpandTiles   = std::vector<std::vector<int>>;
using map_variants  = std::unordered_map<VARIANTS, int>;
using map_animation = std::unordered_map<UI_ANIMATIONS, std::vector<int>>;

struct SpriteData {
    friend class ResourceManager;
    friend class Render;
private:
    SPRITES_SHEETS  source;
    UI_ELEMENTS     type;
    int             id;
    float           width;
    float           height;
    ExpandTiles     vExpandTiles;
    ExpandTiles     hExpandTiles;
    map_animation   animations;
    map_variants    variants;

public:

    Texture2D texture() {
        return RSC::spriteSheets[source]->texture;
    }

    template<typename... Variants>
    Rectangle sourceRect(Variants... variant) {
        int actualId = id;
        actualId += (getIdStep(variant) + ...);

        // Global Data
        auto spriteSheet = RSC::spriteSheets[source];
        auto nbCol       = spriteSheet->columns;
        auto tileWidth   = spriteSheet->tileWidth;
        auto tileHeight  = spriteSheet->tileHeight;

        Rectangle rect = {
                .x = tileWidth   * static_cast<float>(actualId % nbCol),
                .y = tileHeight  * static_cast<float>(actualId / nbCol),
                .width  = width  * tileWidth,
                .height = height * tileHeight
        };

        return rect;
    }

private:
    int getIdStep(VARIANTS variant) {
        auto idStep = variants.find(variant);
        if (idStep == variants.end()) return 0;
        return idStep->second;
    }
};



