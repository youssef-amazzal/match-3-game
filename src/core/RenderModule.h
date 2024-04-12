#pragma once
#include "../headers/Header.h"
#include "TransformModule.h"
#include "../utils/ResourceManager.h"

using TM = TransformModule;

struct RenderModule {

    explicit RenderModule(flecs::world& world) {
        world.import<TransformModule>();

        world.component<Sprite>     ("Sprite");
        world.component<Animation>  ("Animation");
        world.component<Expand>     ("Expand");
        world.component<Variants>   ("Variants");
        world.component<Type>       ("Type");
        world.component<Scale>      ("Scale");
        world.component<Repeat>     ("Repeat");


        world.observer<Type>("InitSprite")
                .event(flecs::OnSet).each(initSprite);

        world.observer<Type, Sprite, Scale, TM::Area>("UpdateScale")
                .event(flecs::OnSet).each(updateScale);

        world.observer<Type, Sprite, Variants>("ApplyVariant")
                .event(flecs::OnSet).each(applyVariant);

        world.system<Sprite, TM::Area, TM::Position>("RepeatRender")
                .with<Repeat>()
                .term_at(3).second<TM::World>()
                .kind(flecs::OnStore)
                .each(repeatRender);

        world.system<Sprite, TM::Area, TM::Position>("RenderSprite")
                .without<Repeat>()
                .term_at(3).second<TM::World>()
                .kind(flecs::OnStore)
                .each(render);

//        world.system().interval(3).with<Sprite>().each([](flecs::entity entity) {
//            std::printf("%s: %-10s\n\n", entity.name().c_str(), entity.type().str().c_str());
//        });
    }

    struct Type;
    struct Sprite;
    struct Layer;
    struct Scale;
    struct Animation;
    struct Expand;
    struct Variants;
    struct Repeat;

private:
    //===================================//
    //             Systems               //
    //===================================//

    static void initSprite(flecs::entity entity, Type& type) {

        if (type.type == UI_ELEMENTS::UI_INVALID) return;

        Scale* scale    = entity.get_mut<Scale>();
        Sprite* sprite  = entity.get_mut<Sprite>();

        TM::Position* position  = entity.get_mut<TM::Position, TM::World>();
        TM::Area* area          = entity.get_mut<TM::Area>();


        auto data = RSC::getSpriteData(type.type);
        SpriteSheet* sheet = data.spriteSheet();

        type.id = data.getId();

        sprite->texture      = &sheet->texture;
        sprite->sourceRect   = data.sourceRect();

        *position = {0, 0};
        area->width = sprite->sourceRect.width    * scale->width   * sheet->scale * UI_SCALE;
        area->height = sprite->sourceRect.height  * scale->height  * sheet->scale * UI_SCALE;
    }

    static void updateScale(Type& type, Sprite& sprite, Scale& scale, TM::Area& area) {
        if (type.type == UI_ELEMENTS::UI_INVALID) return;

        SpriteData data;
        SpriteSheet* sheet;

        data = RSC::getSpriteData(type.type);
        sheet = data.spriteSheet();

        area.width  = sprite.sourceRect.width    * scale.width   * sheet->scale * UI_SCALE;
        area.height = sprite.sourceRect.height   * scale.height  * sheet->scale * UI_SCALE;
    }

    static void applyVariant(Type& type, Sprite& sprite, Variants& variants) {
        if (type.type == UI_ELEMENTS::UI_INVALID) return;

        auto data = RSC::getSpriteData(type.type);
        sprite.sourceRect = data.sourceRect(variants.values);
    }

    static void render(Sprite& sprite, TM::Area& area, TM::Position& position) {
        Rectangle destRect = {
                .x = position.x,
                .y = position.y,
                .width = area.width,
                .height = area.height
        };

        DrawTexturePro(*sprite.texture, sprite.sourceRect, destRect, {0, 0}, 0, WHITE);
    }

    static void repeatRender(Sprite& sprite, TM::Area& area, TM::Position& position) {
        Rectangle destRect = {
                .x = position.x,
                .y = position.y,
                .width = area.width,
                .height = area.height
        };

        for (int i = 0; i < SCREEN_WIDTH / destRect.width; i++) {
            for (int j = 0; j < SCREEN_HEIGHT / destRect.height; j++) {
                destRect.x = destRect.width  * static_cast<float>(i);
                destRect.y = destRect.height * static_cast<float>(j);
                DrawTexturePro(*sprite.texture, sprite.sourceRect, destRect, {0, 0}, 0, WHITE);
            }
        }
    }

    static void renderWithExpansion(Type& type, Sprite& sprite, Expand& expand, const Scale* scale, TM::Area& area, TM::Position& position) {
        if (type.type == UI_ELEMENTS::UI_INVALID) return;

        auto data = RSC::getSpriteData(type.type);
        Rectangle sourceRect = sprite.sourceRect;

        auto vExpandTiles = data.vExpandTiles;
        auto hExpandTiles = data.hExpandTiles;

        int hRepeat = expand.hExpand;
        int vRepeat = expand.vExpand;

        float x = position.x;
        float y = position.y;

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
    };

    struct Layer {
        int zOrder = 0;
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

    struct Repeat {};

};