#include <PCH.h>

#include "Freetype/Window/Window.h"
#include "Scene.h"
#include "Static/Renderer/Renderer.h"
#include "Core/Window/Window.h"
#include "Components/Entity.h"
#include "Core/DebugTools.h"

#include "GameObject.h"
#include "Components/Entity.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Components/Camera.h"
#include "Components/Properties.h"

#include <Bullet.h>

namespace PetrolEngine {
    Entity* Scene::createEntity(const char* name) {
        Entity* entity = new Entity(sceneRegistry.create(), this);
        entities.push_back(entity);
        
        entity->addComponent<Properties>(name);

        return entity;
    }

    GameObject* Scene::createGameObject(const char* name, Entity* parent) {
        GameObject* entity = new GameObject(*createEntity(name));

        auto& transform = entity->addComponent<Transform>();
        entity->transform = &transform;

        if (entity->scene == nullptr) {
            LOG("Entity has no scene", 2);
            throw std::runtime_error("Entity has no scene");
        }

        if (parent)
            transform.parent = &parent->getComponent<Transform>();

        return entity;
    }

	Entity* Scene::getEntityById(uint id) {
        for (auto* entity : entities)
            if (entity->getID() == id) return entity;

        return nullptr;
	}

    Scene::Scene() {
        systemManager = new SystemManager();
        systemManager->scene = this;
        world = new World();
    }

    Scene::~Scene(){
        for(Entity* e : this->entities) delete e;
        delete this->systemManager;
        delete this->world;
    }

    void Scene::start() {
        systemManager->start();
    }

	void Scene::update() { LOG_FUNCTION();
                world->update(deltaTime);
		auto camerasGroup = sceneRegistry.group<Camera>(entt::get<Transform>);
		auto meshesGroup  = sceneRegistry.group< Mesh >(entt::get<Transform>);

		for (auto cameraID : camerasGroup) { LOG_SCOPE("Processing camera view");
			auto& cam = camerasGroup.get<Camera>(cameraID);

            cam.updateView();
			
			for (auto& entity : meshesGroup) {
				LOG_SCOPE("Rendering mesh");

				auto& mesh      = meshesGroup.get<   Mesh  >(entity);
				auto  transform = meshesGroup.get<Transform>(entity);

                Transform t = transform.getRelativeTransform();

				Renderer::renderMesh(mesh, t);
			}
			
		}

        systemManager->update();
    }
}
