#pragma once
#include "../headers/Header.h"
#include "../core/TransformModule.h"

class Scene {
    friend class GameCycle;
    bool isPlaying           = false;

    // this is where any actions that needs to be done every time the scene is played are done
    virtual void enter()     = 0;

    // this is the main loop of the scene
    virtual Scene* update()  = 0;

    // this is where any actions that need to be done when the scene is exited are done
    virtual void exit()      = 0;

protected:
    flecs::world& world;
    flecs::entity* sceneEntity;
    flecs::entity* prevScope;

    explicit Scene(flecs::world& world) : world(world) {}

public:
    virtual ~Scene() {
        world.set_scope(*prevScope);
        sceneEntity->destruct();

        delete sceneEntity;
        delete prevScope;
    };


    // This is the main function that manage the scene lifecycle
    Scene* play() {

        if (!isPlaying) {
            isPlaying = true;

            sceneEntity = new flecs::entity(world, "Scene");
            prevScope   = new flecs::entity(world.set_scope(*sceneEntity));

            sceneEntity
                ->add<TM::Container>()
                .add<TM::Container::Fixed>()
                .set<TM::Position>({0,0})
                .set<TM::Area>({SCREEN_WIDTH, SCREEN_HEIGHT});

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


