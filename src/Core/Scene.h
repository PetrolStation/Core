#pragma once

#include "Core/Aliases.h"

#include <Bullet.h>

namespace PetrolEngine {

    class Entity;
    class GameObject;
    class SystemManager;

    class Scene {
        public:
        Entity* createEntity(const char* name);

        GameObject* createGameObject(const char* name, Entity* parent = nullptr);

        Entity* getEntityById(unsigned int id);

        Scene();
        ~Scene();

        Scene(const Scene&) = delete;
        Scene(Scene&&) = default;

        void update();
        void start();
        
        entt::registry sceneRegistry;
        World* world = nullptr;

        bool isStarted() const { return started; }
    private:
        Vector<Entity*> entities;
        SystemManager* systemManager;
        bool started = false;
        friend class Entity;
        friend class SystemManager;
	};
}


