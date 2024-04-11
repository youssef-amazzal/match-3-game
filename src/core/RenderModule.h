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
        world.observer<Type, Sprite, Scale>().event(flecs::OnSet).each(updateScale);

        world.observer<Type, Sprite, Variants>().event(flecs::OnSet).each(updateSpriteVariant);

        world.system<Sprite>().kind(flecs::OnStore).each(render);
    }

    struct Type;
    struct Sprite;
    struct Scale;
    struct Animation;
    struct Expand;
    struct Variants;

private:
    //===================================//
    //             Systems               //
    //===================================//

    static void initSprite(flecs::entity entity, Type& type) {

        Scale scale;

        if (type.type == UI_ELEMENTS::UI_INVALID) return;

        Sprite sprite;

        auto data = RSC::getSpriteData(type.type);
        SpriteSheet* sheet = data.spriteSheet();

        type.id = data.getId();

        sprite.texture      = &sheet->texture;
        sprite.sourceRect   = data.sourceRect();
        sprite.zOrder       = sheet->layer;

        sprite.destRect     = {
                .x = 0,
                .y = 0,
                .width  = sprite.sourceRect.width    * scale.width   * sheet->scale * UI_SCALE,
                .height = sprite.sourceRect.height   * scale.height  * sheet->scale * UI_SCALE
        };

        entity.set<Sprite>(sprite);
    }

    static void updateScale(Type& type, Sprite& sprite, Scale& scale) {
        if (type.type == UI_ELEMENTS::UI_INVALID) return;

        SpriteData data;
        SpriteSheet* sheet;

        data = RSC::getSpriteData(type.type);
        sheet = data.spriteSheet();

        sprite.destRect.width  = sprite.sourceRect.width    * scale.width   * sheet->scale * UI_SCALE;
        sprite.destRect.height = sprite.sourceRect.height   * scale.height  * sheet->scale * UI_SCALE;
    }



    static void updateSpriteVariant(Type& type, Sprite& sprite, Variants& variants) {
        if (type.type == UI_ELEMENTS::UI_INVALID) return;

        auto data = RSC::getSpriteData(type.type);
        sprite.sourceRect = data.sourceRect(variants.values);
    }

    static void render(flecs::entity entity, Sprite& sprite) {
        Rectangle& sourceRect    = sprite.sourceRect;
        Rectangle& destRect      = sprite.destRect;

        DrawTexturePro(*sprite.texture, sourceRect, destRect, {0, 0}, 0, WHITE);
    }

    static void renderWithExpansion(Type& type, Sprite& sprite, Expand& expand, const Scale* scale) {
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

        float absWidth  = sprite.sourceRect.width   * scale->width  * UI_SCALE;
        float absHeight = sprite.sourceRect.height  * scale->height * UI_SCALE;

        float tileWidth     = sourceRect.width / rWidth;
        float tileHeight    = sourceRect.height / rHeight;
        float absTileWidth  = absWidth / rWidth;
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
        int             zOrder      = 1;
    };

    struct Scale {
        float width = 1.0f;
        float height = 1.0f;
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