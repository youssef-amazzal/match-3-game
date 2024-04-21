#include "RenderModule.h"

#include "../utils/ResourceManager.h"


RM::RenderModule(flecs::world& world) {
    world.import<TransformModule>();
    world.import<AnimationModule>();

    world.observer<Type>("InitSprite")
            .event(flecs::OnSet).each(initSprite);

    world.system<Type, Sprite, Variants, AM::Frame>("updateSourceRect")
            .term_at(4).second<AM::Animation>()
            .kind(flecs::PreStore).each(updateSourceRect);

    world.system<Sprite, Scale, TM::Area>("UpdateScale")
           .without<TM::Container::Fixed>()
           .kind(flecs::PreStore).each(updateScale);

    world.system<Sprite, Scale, TM::Area, const TM::Position, const TM::Depth>("Render")
            .order_by<TM::Depth>([](flecs::entity_t e1, const TM::Depth* d1, flecs::entity_t e2, const TM::Depth* d2) {
                return d1->value - d2->value; // Ascending
            })
            .kind(flecs::OnStore)
            .each(render);
}

//====================================//
//             Observers              //
//====================================//

void RM::initSprite(flecs::entity entity, Type& type) {
    if (type.type == UI_ELEMENTS::UI_INVALID) return;

    Scale*     scale        = entity.get_mut<Scale>();
    Sprite*    sprite       = entity.get_mut<Sprite>();
    Variants*  variants     = entity.get_mut<Variants>();
    AM::Frame* animation    = entity.get_mut<AM::Frame, AM::Animation>();
    auto*      state        = entity.get_mut<AM::Animation::State>();

    TM::Position* position  = entity.get_mut<TM::Position>();
    TM::Area*     area      = entity.get_mut<TM::Area>();

    auto data           = RSC::getSpriteData(type.type);
    SpriteSheet* sheet  = data.spriteSheet();

    sprite->texture      = &sheet->texture;
    sprite->originId     = data.id;
    animation->frames    = data.animations[state->state];

    sprite->sourceRect   = buildSourceRect(type, *sprite, *variants, *animation);

    area->width  = sprite->sourceRect.width   * scale->width  * UI_SCALE;
    area->height = sprite->sourceRect.height  * scale->height * UI_SCALE;
}

//====================================//
//              Systems               //
//====================================//

void RM::updateScale(Sprite& sprite, Scale& scale, TM::Area& area) {
    area.width  = sprite.sourceRect.width    * scale.width    * UI_SCALE;
    area.height = sprite.sourceRect.height   * scale.height   * UI_SCALE;
}

void RM::updateSourceRect(Type& type, Sprite& sprite, Variants& variants, AM::Frame& animation) {
    if (type.type == UI_ELEMENTS::UI_INVALID) return;

    auto data = RSC::getSpriteData(type.type);
    sprite.sourceRect = buildSourceRect(type, sprite, variants, animation);
}

void RM::render(flecs::entity entity, Sprite& sprite, Scale& scale, TM::Area& area, const TM::Position& position, const TM::Depth& depth) {
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


//===================================//
//             Helpers               //
//===================================//

Rectangle RM::buildSourceRect(const Type& type, const Sprite& sprite, const Variants& variants, const AM::Frame& animation) {
    auto data = RSC::getSpriteData(type.type);

    int actualId = sprite.originId;
    for (auto& variant : variants.values) {
        actualId += data.getIdStep(variant);
    }

    actualId += animation.frames[animation.currentFrame];

    // Global Data
    const SpriteSheet* spriteSheet = data.spriteSheet();

    int   nbCol       = spriteSheet->columns;
    float tileWidth   = spriteSheet->tileWidth;
    float tileHeight  = spriteSheet->tileHeight;

    Rectangle rect = {
        .x = tileWidth   * static_cast<float>(actualId % nbCol),
        .y = tileHeight  * static_cast<float>(actualId / nbCol),
        .width  = data.width  * tileWidth,
        .height = data.height * tileHeight
    };

    return rect;
}