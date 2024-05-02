#include "ResourceManager.h"
#include "FileManager.h"

std::unordered_map<SPRITES_SHEETS, std::shared_ptr<SpriteSheet>> ResourceManager::spriteSheets;
std::unordered_map<UI_ELEMENTS, SpriteData> ResourceManager::sprites;

//==============================//
//          Loaders             //
//==============================//

///------------------------- TEXTURES -------------------------//

void RSC::loadTextures() {
    loadSpriteSheets();
    loadSprites();
}

void RSC::loadSpriteSheets() {
    json parsed = FileManager::readJson(SPRITESHEETS_DATA);

    for (const auto& item : parsed) {
        auto spriteSheetPtr = std::make_shared<SpriteSheet>();
        *spriteSheetPtr = item.get<SpriteSheet>();

        if (spriteSheetPtr->type != SP_INVALID) {
            std::string texturePath = (ROOT_PATH / item.at("path")).string();
            spriteSheetPtr->texture = LoadTexture(texturePath.c_str());
            spriteSheets[spriteSheetPtr->type] = spriteSheetPtr;
        }
    }
}

void RSC::loadSprites() {
    json parsedSheets = FileManager::readJson(SPRITES_DATA);

    for (const auto& item: parsedSheets) {
        SPRITES_SHEETS sheetType = item.at("spritesheet").get<SPRITES_SHEETS>();

        if (spriteSheets.count(sheetType) > 0) {
            loadIndividualSprites(item, sheetType);
        } else {
            std::cerr << item.at("spritesheet") << " sheet isn't loaded" << '\n';
        }
    }
}

void RSC::loadIndividualSprites(const json& item, SPRITES_SHEETS sheetType) {
    auto spriteJson = item.at("sprites");

    for (const auto& sprite : spriteJson) {
        SpriteData data;

        data.source = sheetType;
        data.type = sprite.at("type").get<UI_ELEMENTS>();
        data.id = sprite.at("baseId");
        data.width = sprite.at("width");
        data.height = sprite.at("height");

        loadAnimations(sprite, data);
        loadExpansions(sprite, data);
        loadVariants(sprite, data);

        sprites[data.type] = data;
    }
}

void RSC::loadAnimations(const json& sprite, SpriteData& data) {
    for (const auto& animation : sprite.at("animations")) {
        auto frames = animation.at("frames").get<std::vector<int>>();
        data.animations[animation.at("type").get<ANIMATIONS>()] = frames;
    }
}

void RSC::loadExpansions(const json& sprite, SpriteData& data) {
    for (const auto& expansion : sprite.at("expansions")) {
        UI_EXPANSION type = expansion.at("type").get<UI_EXPANSION>();
        std::vector<std::vector<int>> values = expansion.at("value").get<std::vector<std::vector<int>>>();

        (type == EX_HORIZONTAL) ? data.hExpandTiles = values : data.vExpandTiles = values;
    }
}

void RSC::loadVariants(const json& sprite, SpriteData& data) {
    for (const auto& variant : sprite.at("variants")) {
        auto values = variant.at("values");
        for (const auto& value : values) {
            data.variants[value.at("name").get<VARIANTS>()] = value.at("idStep");
        }
    }
}


///------------------------- SCENES -------------------------//


//==============================//
//            Getters           //
//==============================//

SpriteData& RSC::getSpriteData(UI_ELEMENTS type) {
    return sprites[type];
}


