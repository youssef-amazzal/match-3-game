#pragma once
#include "../headers/Header.h"
#include "../core/RenderModule.h"
#include "../core/TransformModule.h"
#include "../UI/HUD.h"

class Scene {
    friend class Game;
private:
    flecs::entity* prevScope = nullptr;
    bool isPlaying           = false;

    // this is where any actions that needs to be done every time the scene is played are done
    virtual void enter()     = 0;

    // this is the main loop of the scene
    virtual Scene* update()  = 0;

    // this is where any actions that need to be done when the scene is exited are done
    virtual void exit()      = 0;

protected:
    flecs::world& world;
    flecs::entity* sceneEntity = nullptr;
    Scene(flecs::world& world) : world(world){
        sceneEntity = new flecs::entity(world);
        prevScope   = new flecs::entity(world);
    };

    template<class T>
    static Scene* getInstance(flecs::world& world) {

        if constexpr (std::is_base_of<Scene, T>::value) {
            static_assert(std::is_base_of<Scene, T>::value, "T must inherit from Scene");
        }

        static std::unique_ptr<Scene> instance = std::make_unique<T>(T(world));
        return instance.get();
    }

public:
    virtual ~Scene() {
        sceneEntity->destruct();
        prevScope->destruct();
        delete sceneEntity;
    };


    // This is the main function that manage the scene lifecycle
    Scene* play() {

        if (!isPlaying) {
            isPlaying = true;

            // scope the world to the scene so that all entities created in the scene are children of the scene
            *prevScope = world.set_scope(*sceneEntity);
            enter();
        }

        auto nextSceen = update();

        if (nextSceen) {
            isPlaying = false;

            exit();

            // remove all entities created in the scene
            world.delete_with(flecs::ChildOf, *sceneEntity);

            // reset the world scope to the previous scope
            world.set_scope(*prevScope);
        }

        return nextSceen;
    }

};


