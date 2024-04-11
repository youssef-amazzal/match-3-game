#pragma once
#include "../headers/Header.h"
#include "../utils/ResourceManager.h"

struct RenderModule {

    explicit RenderModule(flecs::world& world) {

        world.component<Sprite>("Sprite");
        world.component<Animation>("Animation");
        world.component<Expand>("Expand");
        world.component<Variants>("Variants");
        world.component<Type>("Type");

        world.observer<Type, Sprite, Variants>().event(flecs::OnSet).each(updateSpriteVariant);
        world.system<Sprite>().kind(flecs::OnStore).each(renderSprite);

    }

    static void init(flecs::world& world) {
        auto query = world.query<Type, Sprite>();

        query.each(initSprite);
    }

    struct Type {
        UI_ELEMENTS type;
        int id;
    };

    struct Sprite {
        Texture2D*      texture     = nullptr;
        Rectangle       sourceRect  = {0, 0, 0, 0};
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
        int hExpand;
        int vExpand;
    };

    struct Variants {
        std::vector<VARIANTS> values;
    };

private:
    //===================================//
    //             Systems               //
    //===================================//

    static void initSprite(Type& type, Sprite& sprite) {

        if (type.type == UI_ELEMENTS::UI_INVALID) return;

        auto data = RSC::getSpriteData(type.type);
        SpriteSheet* sheet = data.spriteSheet();

        type.id = data.getId();

        sprite.texture      = &sheet->texture;
        sprite.sourceRect   = data.sourceRect();
        sprite.xScale       = sheet->scale;
        sprite.yScale       = sheet->scale;
        sprite.zOrder       = sheet->layer;
    }

    static void updateSpriteVariant(Type& type, Sprite& sprite, Variants& variants) {
        if (type.type == UI_ELEMENTS::UI_INVALID) return;

        auto data = RSC::getSpriteData(type.type);
        sprite.sourceRect = data.sourceRect(variants.values);
    }

    static void renderSprite(Sprite& sprite) {
        DrawTexturePro(*sprite.texture, sprite.sourceRect, {100, 100, 64, 64}, {0, 0}, 0, WHITE);
    }
};