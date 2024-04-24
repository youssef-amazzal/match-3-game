#include "AnimationModule.h"
#include "InputModule.h"
#include "RenderModule.h"
#include "../utils/ResourceManager.h"

AM::AnimationModule(flecs::world& world) {
    world.import<InputModule>();
    world.import<TransformModule>();
    world.observer<RM::Type, Animation::State>("OnSet:AnimationState")
            .event(flecs::OnSet).each([](flecs::entity entity, RM::Type& type, Animation::State& state) {
                auto data = RSC::getSpriteData(type.type);
                auto animation = entity.get_mut<Frame, Animation>();

                // Grab the new set of frames and reset the current frame
                animation->frames = data.animations[state.state];
                animation->currentFrame = 0;
            });

    world.system<Frame>("UpdateFrameAnimation")
        .term_at(1).second<Animation>()
        .kind(flecs::PreStore)
        .each(updateFrame);

    world.system<Linear, TM::Position>("UpdateLinearAnimation")
        .term_at(1).second<Animation>()
        .kind(flecs::PreStore)
        .each(updateLinear);

    world.system<IM::Mouse>("UpdateInteractivity")
        .each(updateInteractivity);
}

void AM::updateFrame(Frame& frame) {
    frame.frameTime += GetFrameTime();

    // Advance to the next frame when the time is right
    const int ANIMATION_FRAME_RATE = 12;

    if (frame.frameTime >= 1.0 / ANIMATION_FRAME_RATE) {
        frame.currentFrame++;
        frame.frameTime = 0;
    }

    if (frame.currentFrame >= frame.frames.size()) {
        frame.currentFrame = 0;
    }
}

void AM::updateLinear(Linear& linear, TM::Position& position) {
    // Calculate the total distance to travel
    float totalDistance = sqrt(pow(linear.end.x - linear.start.x, 2) + pow(linear.end.y - linear.start.y, 2));

    // Calculate the speed needed to travel the total distance in the desired duration
    float speed = totalDistance / linear.duration;

    // Calculate the normalized direction vector
    Vector2 direction = {
        (linear.end.x - linear.start.x) / totalDistance,
        (linear.end.y - linear.start.y) / totalDistance
    };

    // Update the position
    position.x += speed * direction.x * GetFrameTime();
    position.y += speed * direction.y * GetFrameTime();

    // Check if the current position has reached the end position
    bool hasReachedEnd = position.x >= linear.end.x && position.y >= linear.end.y;

    // If the end is reached, reset the position to the start
    if (hasReachedEnd) {
        position.x = linear.start.x;
        position.y = linear.start.y;
    }
}

void AM::updateInteractivity(flecs::entity entity, const IM::Mouse mouse) {
    ANIMATIONS state = ANIMATIONS::IDLE;

    // std::cout << entity.name() << std::endl;

    if (mouse.isHovered)      state = ANIMATIONS::HOVER;
    if (mouse.isLeftPressed)  state = ANIMATIONS::PRESS;
    if (mouse.isRightPressed) state = ANIMATIONS::PRESS;

    entity.set<Animation::State>({state});
}
