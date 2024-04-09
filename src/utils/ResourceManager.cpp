#include "ResourceManager.h"
#include "FileManager.h"

std::map<SPRITES, SpriteSheet*> ResourceManager::spriteSheets;

void ResourceManager::loadTextures() {
    loadSpriteSheets();
    loadSprites();
}

void ResourceManager::loadSpriteSheets() {
    std::string path = "spritesheets.json";
    SpriteSheet* spriteSheetPtr;

    json parsed = FileManager::parseJson(path, FileManager::SPRITES_PATH);

    for (const auto& item : parsed) {
        spriteSheetPtr = new SpriteSheet;
        *spriteSheetPtr = item.get<SpriteSheet>();

        if (spriteSheetPtr->type != SP_INVALID) {
            std::string texturePath = (FileManager::ROOT_PATH / item.at("path")).string();
            spriteSheetPtr->texture = LoadTexture(texturePath.c_str());
            spriteSheets[spriteSheetPtr->type] = spriteSheetPtr;
        }
    }
}

void ResourceManager::loadSprites() {
    std::string path = "sprites.json";
    json parsedSheets = FileManager::parseJson(path, FileManager::SPRITES_PATH);

    // iterate over spritesheets
    for (const auto& item: parsedSheets) {
        try {
            SpriteSheet* sheet = spriteSheets.at(item.at("spritesheet").get<SPRITES>());
            auto sprites = item.at("sprites");

            // iterate over individual sprites
            for (const auto& sprite : sprites) {
                SpriteData data;
                data.type = sprite.at("type").get<UI_ELEMENTS>();
                data.id = sprite.at("baseId");
                data.width = sprite.at("width");
                data.height = sprite.at("height");

                // grab its animations frames
                for (const auto& animation : sprite.at("animations")) {
                    auto frames = animation.at("frames").get<std::vector<int>>();
                    data.animations[animation.at("type").get<UI_ANIMATIONS>()] = frames;
                }

                // grab its expansion tiles
                for (const auto& expansion : sprite.at("expansions")) {
                    UI_EXPANSION type = expansion.at("type").get<UI_EXPANSION>();
                    std::vector<std::vector<int>> values = expansion.at("value").get<std::vector<std::vector<int>>>();

                    (type == EX_HORIZONTAL) ? data.hExpandTiles = values : data.vExpandTiles = values;
                }

                // grab its variants
                for (const auto& variant : sprite.at("variants")) {
                    auto values = variant.at("values");
                    for (const auto& value : values) {
                        data.variants[variant.at("type").get<VARIANTS>()][value.at("name").get<VARIANTS>()] = value.at("idStep");
                    }
                }


                sheet->sprites[data.type] = data;
            }

        } catch (std::out_of_range &e) {
            std::cerr << item.at("spritesheet") << " sheet isn't loaded" << '\n';
            std::cerr << e.what() << '\n';
        }
    }
}