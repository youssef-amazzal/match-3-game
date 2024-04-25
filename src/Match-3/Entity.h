#pragma once
#include "../headers/Header.h"
#include "../core/TransformModule.h"
#include "../core/RenderModule.h"

template<typename T>
struct Entity : flecs::entity {

    Entity(const Entity& entity) = default;
    Entity(const flecs::world& world, const flecs::id id) : flecs::entity(world, id) {}
    Entity(const flecs::world& world, const flecs::entity entity) : flecs::entity(world, entity) {}

    explicit Entity(const flecs::world& world) : flecs::entity(world) {}

    Entity(const flecs::world& world, const std::string& name) : flecs::entity(world) {
        this->set_name((name + std::to_string(this->id())).c_str());
    }

    T& setContainer(const flecs::entity& container) {
        this->add<TM::ContainedBy>(container);
        return static_cast<T&>(*this);
    }

    T& expand(const int expansion) {
        this->set<RM::Expandable>({expansion, 1});
        return static_cast<T&>(*this);
    }

    T& type(UI_ELEMENTS type) {
        this->set<RM::Type>({type});
        return static_cast<T&>(*this);
    }

    T& scale(const float scale) {
        this->set<RM::Scale>({scale, scale});
        return static_cast<T&>(*this);
    }

    T& setVariant(const std::vector<VARIANTS>& variants) {
        this->set<RM::Variants>({variants});
        return static_cast<T&>(*this);
    }

    bool operator==(const T& entity) {
        return this->id() == entity.id();
    }

protected:
    std::vector<flecs::entity>& getSlots() {
        return this->get_mut<TM::Container::Content>()->items;
    }
};