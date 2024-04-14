#pragma once
#include "../headers/Header.h"
#include "../core/RenderModule.h"
#include "../core/TransformModule.h"
#include "../core/UiModule.h"

class Scene {
    friend class Game;
private:
    bool isPlaying           = false;

    // this is where any actions that needs to be done every time the scene is played are done
    virtual void enter()     = 0;

    // this is the main loop of the scene
    virtual Scene* update()  = 0;

    // this is where any actions that need to be done when the scene is exited are done
    virtual void exit()      = 0;

protected:
    flecs::world& world;
    flecs::entity sceneEntity;
    flecs::entity prevScope;

    explicit Scene(flecs::world& world) : world(world), sceneEntity(world.entity("Scene")), prevScope(world.set_scope(sceneEntity)) {
        world.set_scope(sceneEntity);

        sceneEntity
                .set<RM::Type>({UI_ELEMENTS::UI_BG_PATTERN})
                .add<RM::Repeat>()
                .add<TM::Container>()
                .add<TM::Container::Fixed>()
                .set<TM::Depth>({0})
                .set<TM::Position>({0,0})
                .set<TM::Area>({SCREEN_WIDTH, SCREEN_HEIGHT});

    };

public:
    virtual ~Scene() {
        world.set_scope(prevScope);
        sceneEntity.destruct();
    };


    // This is the main function that manage the scene lifecycle
    Scene* play() {

        if (!isPlaying) {
            isPlaying = true;
            // scope the world to the scene so that all entities created in the scene are children of the scene
            enter();

        }


        auto nextScene = update();


        if (nextScene) {
            isPlaying = false;

            exit();

            // reset the world scope to the previous scope
        }


        return nextScene;
    }

};


