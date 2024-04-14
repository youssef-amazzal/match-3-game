#pragma once
#include "../headers/Header.h"
#include "TransformModule.h"
#include "../utils/ResourceManager.h"

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

        world.observer<Sprite, Scale, TM::Area>("UpdateScale")
                .without<TM::Container::Fixed>()
                .event(flecs::OnSet).each(updateScale);

        world.observer<Type, Sprite, Variants>("ApplyVariant")
                .event(flecs::OnSet).each(applyVariant);


        world.system<Sprite, Scale, TM::Area, const TM::Position, const TM::Depth>("Render")
                .order_by<TM::Depth>([](flecs::entity_t e1, const TM::Depth* d1, flecs::entity_t e2, const TM::Depth* d2) {
                    return d1->value - d2->value; // Ascending
                })
                .kind(flecs::OnStore)
                .each(render);


        world.system().with<Sprite>().each([](flecs::entity entity) {
            if (IsKeyPressed(KEY_LEFT_ALT)) {
                std::printf("%s: %-10s\n\n", entity.name().c_str(), entity.type().str().c_str());
            }
        });
    }

    struct Type;
    struct Sprite;
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

        Scale*  scale    = entity.get_mut<Scale>();
        Sprite* sprite   = entity.get_mut<Sprite>();

        TM::Position* position  = entity.get_mut<TM::Position>();
        TM::Area*     area      = entity.get_mut<TM::Area>();

        auto data = RSC::getSpriteData(type.type);
        SpriteSheet* sheet  = data.spriteSheet();

        sprite->texture      = &sheet->texture;
        sprite->sourceRect   = data.sourceRect();

        *position = {0, 0};
        area->width  = sprite->sourceRect.width   * scale->width  * UI_SCALE;
        area->height = sprite->sourceRect.height  * scale->height * UI_SCALE;
    }

    static void updateScale(Sprite& sprite, Scale& scale, TM::Area& area) {
        area.width  = sprite.sourceRect.width    * scale.width    * UI_SCALE;
        area.height = sprite.sourceRect.height   * scale.height   * UI_SCALE;
    }

    static void applyVariant(Type& type, Sprite& sprite, Variants& variants) {
        if (type.type == UI_ELEMENTS::UI_INVALID) return;

        auto data = RSC::getSpriteData(type.type);
        sprite.sourceRect = data.sourceRect(variants.values);
    }

    static void render(flecs::entity entity, Sprite& sprite, Scale& scale, TM::Area& area, const TM::Position& position, const TM::Depth& depth) {
        float scaledTileWidth  = area.width;
        float scaledTileHeight = area.height;
        auto hGap = 0, vGap = 0;

        if (entity.has<Repeat>()) {
            switch (entity.get<Repeat>()->type) {

                case Repeat::HORIZONTAL:
                    scaledTileWidth  = area.height;
                    scaledTileHeight = area.height;
                    hGap = entity.get_mut<TM::Container::Gap>()->value;
                    break;

                case Repeat::VERTICAL:
                    scaledTileWidth  = area.width;
                    scaledTileHeight = area.width;
                    vGap = entity.get_mut<TM::Container::Gap>()->value;
                    break;

                case Repeat::BOTH:
                    scaledTileWidth  = sprite.sourceRect.width     * scale.width     * UI_SCALE;
                    scaledTileHeight = sprite.sourceRect.height    * scale.height    * UI_SCALE;

                    hGap = entity.get_mut<TM::Container::Gap>()->value;
                    vGap = entity.get_mut<TM::Container::Gap>()->value;
                    break;
            }
        }

        Rectangle destRect = {
                .x = position.x,
                .y = position.y,
                .width  = scaledTileWidth,
                .height = scaledTileHeight
        };

        double rows = area.height / destRect.height;
        double cols = area.width / destRect.width;

        // Special case for background
        if (entity.name() == "Scene") {
            rows = ceil(rows);
            cols = ceil(cols);
        } else {
            rows = floor(rows);
            cols = floor(cols);
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                destRect.x = position.x + destRect.width  * static_cast<float>(j);
                destRect.y = position.y + destRect.height * static_cast<float>(i);
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
    };

    struct Sprite {
        Texture2D*  texture     = nullptr;
        Rectangle   sourceRect  = {0, 0, 0, 0};
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

    struct Repeat {
        enum Type {
            HORIZONTAL,
            VERTICAL,
            BOTH
        } type = BOTH;
    };

};

using RM = RenderModule;