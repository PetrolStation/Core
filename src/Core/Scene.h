#pragma once

#include "Core/Aliases.h"

namespace PetrolEngine {

    class Entity;
    class GameObject;
    class SystemManager;

    uint64_t timeMillisec();

    class Scene {
        public:
        Entity* createEntity(const char* name);

        GameObject* createGameObject(const char* name, Entity* parent = nullptr);

        Entity* getEntityById(unsigned int id);

        template<typename T>
        Entity* getEntityByComponent() {
            auto group = sceneRegistry.view<T>();

            for (auto &entity: group)
                return getEntityById((unsigned int)entity);

            return nullptr;
        }

        Scene();
        ~Scene();

        Scene(const Scene&) = delete;
        Scene(Scene&&) = default;

        void update();
        void start();
        
        entt::registry sceneRegistry;

        bool isStarted() const { return started; }
    private:
        Vector<Entity*> toDelete;
        Vector<Entity*> entities;
        SystemManager* systemManager;
        bool started = false;
        friend class Entity;
        friend class SystemManager;
	};
}


