#pragma once
#include "../headers/Header.h"

class Scene {
    friend class Game;
private:
    bool isPlaying = false;
    virtual void enter() = 0;
    virtual void exit()  = 0;
    virtual Scene* update() = 0;

protected:
    flecs::entity* sceneEntity = nullptr;
    Scene() = default;

    template<class T>
    static Scene* getInstance() {

        if constexpr (std::is_base_of<Scene, T>::value) {
            static_assert(std::is_base_of<Scene, T>::value, "T must inherit from Scene");
        }

        static std::unique_ptr<Scene> instance = std::make_unique<T>();
        return instance.get();
    }

public:
    virtual ~Scene() = default;


    Scene* play() {

        if (!isPlaying) {
            isPlaying = true;
            enter();
        }

        auto nextSceen = update();

        if (nextSceen) {
            isPlaying = false;
            exit();
        }

        return nextSceen;
    }

};


