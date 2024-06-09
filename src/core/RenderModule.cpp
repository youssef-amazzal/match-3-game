#include "RenderModule.h"

#include "../utils/ResourceManager.h"


RM::RenderModule(flecs::world& world) {
    world.import<TransformModule>();
    world.import<AnimationModule>();

    world.observer<Sprite::Key>("InitSprite")
            .event(flecs::OnSet).each(initSprite);

    world.observer<RM::Text>("OnSet:Text")
            .event(flecs::OnSet)
            .each([](flecs::entity entity, RM::Text& text) {
                auto area = entity.get_mut<TM::Area>();
                Vector2 textArea = MeasureTextEx(GetFontDefault(), text.text.c_str(), text.fontSize, text.spacing);
                area->width = textArea.x;
                area->height = textArea.y;
            });


    world.system<Sprite::Key, Sprite, Variants, AM::Frame>("updateSourceRect")
            .term_at(4).second<AM::Animation>()
            .kind(flecs::PreStore).each(updateSourceRect);

    world.system<Sprite, Scale, TM::Area>("UpdateScale")
           .without<TM::Container::Fixed>()
           .kind(flecs::PreStore).each(updateScale);

    world.system<Sprite::Key, Sprite, Scale, TM::Area, const TM::Position, const TM::Depth>("Render")
            .order_by<TM::Depth>([](flecs::entity_t e1, const TM::Depth* d1, flecs::entity_t e2, const TM::Depth* d2) {
                return d1->value - d2->value; // Ascending
            })
            .kind(flecs::OnStore)
            .each(render);

    world.system<Text, const TM::Position, const TM::Depth>("RenderText")
            .order_by<TM::Depth>([](flecs::entity_t e1, const TM::Depth* d1, flecs::entity_t e2, const TM::Depth* d2) {
                return d1->value - d2->value; // Ascending
            })
            .kind(flecs::OnStore)
            .each(renderText);
}

//====================================//
//             Observers              //
//====================================//

void RM::initSprite(flecs::entity entity, Sprite::Key& type) {
    if (type.key == UI_ELEMENTS::UI_INVALID) return;

    Scale*     scale        = entity.get_mut<Scale>();
    Opacity*   opacity      = entity.get_mut<Opacity>();
    Sprite*    sprite       = entity.get_mut<Sprite>();
    Variants*  variants     = entity.get_mut<Variants>();
    AM::Frame* animation    = entity.get_mut<AM::Frame, AM::Animation>();
    auto*      state        = entity.get_mut<AM::Animation::State>();

    TM::Position* position  = entity.get_mut<TM::Position>();
    TM::Area*     area      = entity.get_mut<TM::Area>();

    auto data           = RSC::getSpriteData(type.key);
    SpriteSheet* sheet  = data.spriteSheet();

    sprite->texture      = &sheet->texture;
    sprite->originId     = data.id;
    animation->frames    = data.animations[state->state];

    sprite->sourceRect   = buildSourceRect(type, *sprite, *variants, *animation);
}

//====================================//
//              Systems               //
//====================================//

void RM::updateScale(flecs::entity entity, Sprite& sprite, Scale& scale, TM::Area& area) {
    area.width  = sprite.sourceRect.width    * scale.width    * UI_SCALE;
    area.height = sprite.sourceRect.height   * scale.height   * UI_SCALE;


    // Expandable: Get the Expandable component
    auto* expandable = entity.get<Expandable>();

    if (expandable) {
        // Expandable: Calculate the dimensions of each tile
        auto data = RSC::getSpriteData(entity.get<Sprite::Key>()->key);

        float tileWidth  = area.width / data.width;
        float tileHeight = area.height / data.height;

        // Expandable: Calculate the dimensions of the expanded sprite
        float expandedWidth  = tileWidth  * (expandable->horizontal - 1);
        float expandedHeight = tileHeight * (expandable->vertical - 1);

        // Expandable: Update the area dimensions
        area.width  = expandedWidth  + area.width;
        area.height = expandedHeight + area.height;
    }
}

void RM::updateSourceRect(Sprite::Key& type, Sprite& sprite, Variants& variants, AM::Frame& animation) {
    if (type.key == UI_ELEMENTS::UI_INVALID) return;

    auto data = RSC::getSpriteData(type.key);
    sprite.sourceRect = buildSourceRect(type, sprite, variants, animation);
}

void RM::render(flecs::entity entity, Sprite::Key& type, Sprite& sprite, Scale& scale, TM::Area& area, const TM::Position& position, const TM::Depth& depth) {
    float scaledTileWidth  = sprite.sourceRect.width      * scale.width      * UI_SCALE;
    float scaledTileHeight = sprite.sourceRect.height     * scale.height     * UI_SCALE;


    // Calculate the individual tile size based on the repeat type
    if (entity.has<Repeat>()) {
        switch (entity.get<Repeat>()->type) {

            case Repeat::HORIZONTAL:
                scaledTileWidth  = scaledTileHeight;
                break;

            case Repeat::VERTICAL:
                scaledTileHeight = scaledTileWidth;
                break;

            case Repeat::BOTH:
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
    if (entity.name().contains("Scene") || entity.name().contains("Background")) {
        rows = ceil(rows);
        cols = ceil(cols);
    } else {
        rows = floor(rows);
        cols = floor(cols);
    }


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (entity.has<Expandable>()) {
                renderExpandableTiles(entity, destRect);
            } else {
                destRect.x = position.x + destRect.width  * static_cast<float>(j);
                destRect.y = position.y + destRect.height * static_cast<float>(i);
                DrawTexturePro(*sprite.texture, sprite.sourceRect, destRect, {0, 0}, 0, WHITE);
            }
        }
    }
}

void drawTiles(const SpriteData& data, const RM::Sprite& sprite, const RM::Expandable& expandable, const TM::Position& position, float tileWidth, float tileHeight, float destTileWidth, float destTileHeight, int row, float verticalOffset) {
    for (int v = 0; v < (data.vExpandTiles[row][0] ? expandable.vertical : 1); v++) {
        float horizontalOffset = 0;
        for (int col = 0; col < data.width; col++) {
            Rectangle sourceTileRect = {
                .x = sprite.sourceRect.x + tileWidth * col,
                .y = sprite.sourceRect.y + tileHeight * row,
                .width = tileWidth,
                .height = tileHeight
            };

            Rectangle destTileRect = {
                .x = position.x + destTileWidth * (col + horizontalOffset),
                .y = position.y + destTileHeight * (row + v + verticalOffset),
                .width = destTileWidth,
                .height = destTileHeight
            };

            if (data.hExpandTiles[row][col]) {
                for (int h = 0; h < expandable.horizontal; h++) {
                    destTileRect.x = position.x + destTileWidth * (col + h);
                    DrawTexturePro(*sprite.texture, sourceTileRect, destTileRect, {0, 0}, 0, WHITE);
                }
                if (expandable.horizontal > 1) {
                    horizontalOffset += expandable.horizontal - 1;
                }
            } else {
                DrawTexturePro(*sprite.texture, sourceTileRect, destTileRect, {0, 0}, 0, WHITE);
            }
        }
    }
}

void RM::renderExpandableTiles(const flecs::entity entity, const Rectangle destRect) {
    auto sprite = *entity.get<Sprite>();
    auto type   = *entity.get<Sprite::Key>();
    auto position = *entity.get<TM::Position>();


    // Expandable: Get the Expandable component
    auto* expandable = entity.get<Expandable>();
    if (!expandable) {
        return;
    }

    SpriteData data = RSC::getSpriteData(type.key);

    // Expandable: Calculate the dimensions of each tile
    float tileWidth  = sprite.sourceRect.width / data.width;
    float tileHeight = sprite.sourceRect.height / data.height;

    // Expandable: Calculate the dimensions of each destination tile
    float destTileWidth  = destRect.width / data.width;
    float destTileHeight = destRect.height / data.height;

    float verticalOffset = 0;
    for (int row = 0; row < data.height; row++) {
        drawTiles(data, sprite, *expandable, position, tileWidth, tileHeight, destTileWidth, destTileHeight, row, verticalOffset);
        if (data.vExpandTiles[row][0] && expandable->vertical > 1) {
            verticalOffset += expandable->vertical - 1;
        }
    }
}



void RM::renderText(flecs::entity entity, Text& text, const TM::Position& position, const TM::Depth& depth) {
    DrawTextEx(
        GetFontDefault(),
        text.text.c_str(),
        {position.x, position.y},
        text.fontSize * UI_SCALE,
        text.spacing,
        WHITE
    );
}


//===================================//
//             Helpers               //
//===================================//

Rectangle RM::buildSourceRect(const Sprite::Key& type, const Sprite& sprite, const Variants& variants, const AM::Frame& animation) {
    auto data = RSC::getSpriteData(type.key);

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