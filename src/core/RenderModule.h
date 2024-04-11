#pragma once
#include "../headers/Header.h"
#include "../utils/ResourceManager.h"



struct RenderModule {

    explicit RenderModule(flecs::world& world) {
        world.component<Sprite>     ("Sprite");
        world.component<Animation>  ("Animation");
        world.component<Expand>     ("Expand");
        world.component<Variants>   ("Variants");
        world.component<Type>       ("Type");

        world.observer<Type>().event(flecs::OnSet).each(initSprite);
        world.observer<Type, Sprite, Variants>().event(flecs::OnSet).each(updateSpriteVariant);

        world.system<Sprite>().kind(flecs::OnStore).each(render);
    }

    struct Type;
    struct Sprite;
    struct Animation;
    struct Expand;
    struct Variants;

private:
    //===================================//
    //             Systems               //
    //===================================//

    // TODO: Find a way to assure that the sprite is initialized before using it (.add<Sprite>() doesn't do that currently)

    static void initSprite(flecs::entity entity, Type& type) {

        if (type.type == UI_ELEMENTS::UI_INVALID) return;

        Sprite sprite;

        auto data = RSC::getSpriteData(type.type);
        SpriteSheet* sheet = data.spriteSheet();

        type.id = data.getId();

        sprite.texture      = &sheet->texture;
        sprite.sourceRect   = data.sourceRect();
        sprite.xScale       = sheet->scale;
        sprite.yScale       = sheet->scale;
        sprite.zOrder       = sheet->layer;

        sprite.destRect     = {
                .x = 0,
                .y = 0,
                .width = sprite.sourceRect.width * sprite.xScale * UI_SCALE,
                .height = sprite.sourceRect.height * sprite.yScale * UI_SCALE
        };

        entity.set<Sprite>(sprite);
    }

    static void updateSpriteVariant(Type& type, Sprite& sprite, Variants& variants) {
        std::cout << "Updating Sprite Variant" << std::endl;

        if (type.type == UI_ELEMENTS::UI_INVALID) return;

        std::cout << "Updating Sprite Variant Passed" << std::endl;

        auto data = RSC::getSpriteData(type.type);
        sprite.sourceRect = data.sourceRect(variants.values);
    }

    static void render(flecs::entity entity, Sprite& sprite) {
        Rectangle& sourceRect    = sprite.sourceRect;
        Rectangle& destRect      = sprite.destRect;

        DrawTexturePro(*sprite.texture, sourceRect, destRect, {0, 0}, 0, WHITE);
    }

    static void renderWithExpansion(Type& type, Sprite& sprite, Expand& expand) {
        if (type.type == UI_ELEMENTS::UI_INVALID) return;

        auto data = RSC::getSpriteData(type.type);
        Rectangle sourceRect = sprite.sourceRect;

        auto vExpandTiles = data.vExpandTiles;
        auto hExpandTiles = data.hExpandTiles;

        int hRepeat = expand.hExpand;
        int vRepeat = expand.vExpand;

        float x = sprite.destRect.x;
        float y = sprite.destRect.y;

        float rWidth  = data.width;
        float rHeight = data.height;

        float absWidth = sprite.sourceRect.width * sprite.xScale * UI_SCALE;
        float absHeight = sprite.sourceRect.height * sprite.yScale * UI_SCALE;

        float tileWidth = sourceRect.width / rWidth;
        float tileHeight = sourceRect.height / rHeight;
        float absTileWidth = absWidth / rWidth;
        float absTileHeight = absHeight / rHeight;

        for (int i = 0; i < rHeight; i++) {
            for (int j = 0; j < rWidth; j++) {
                Rectangle tileSource = {
                        .x = sourceRect.x + tileWidth * static_cast<float>(j),
                        .y = sourceRect.y + tileHeight * static_cast<float>(i),
                        .width = sourceRect.width / rWidth,
                        .height = sourceRect.height / rHeight
                };

                Rectangle tileDest = {
                        .x = x + absTileWidth * static_cast<float>(j),
                        .y = y + absTileHeight * static_cast<float>(i),
                        .width = absWidth / rWidth,
                        .height = absHeight / rHeight
                };
            }
        }

    }

public:

    struct Type {
        UI_ELEMENTS type    = UI_ELEMENTS::UI_INVALID;
        int id              = 0;
    };

    struct Sprite {
        Texture2D*      texture     = nullptr;
        Rectangle       sourceRect  = {0, 0, 0, 0};
        Rectangle       destRect    = {0, 0, 0, 0};
        float           xScale      = 1.0f;
        float           yScale      = 1.0f;
        int             zOrder      = 1;
    };

    struct Animation {
        ANIMATIONS       state = ANIMATIONS::IDLE;
        std::vector<int> frames{};
        int              currentFrame = 0;
    };

    struct Expand {
        int hExpand = 1;
        int vExpand = 1;
    };

    struct Variants {
        std::vector<VARIANTS> values;
    };

};