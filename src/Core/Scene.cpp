#include <PCH.h>
#include <vector>

#include "Static/Window/Window.h"
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
#include "Components/Sprite.h"

namespace PetrolEngine {

    uint64_t timeMillisec() {
        using namespace std::chrono;
        uint64_t time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        static const uint64_t f = time;
        return time - f;
    }

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
    }

    Scene::~Scene(){
        for(Entity* e : this->entities) delete e;
        delete this->systemManager;
    }

    void Scene::start() {
        if (this->started) return;

        deltaTime = timeMillisec();
        systemManager->start();

        this->started = true;
    }

	void Scene::update() { LOG_FUNCTION();
	    static uint64 previousTime = deltaTime;
        uint64 now = timeMillisec();
        deltaTime = (now - previousTime) / 1000.f;
        previousTime = now;
    
        for(auto a : EventStack::getEvents<WindowApi::WindowResizedEvent>()){
            Renderer::setViewport(0, 0, a->data.width, a->data.height);
        }
        
        systemManager->update();
        //std::cout<<"why is "<<toDelete.size()<<" elements here\n";
	    for(Entity* entity : toDelete) this->sceneRegistry.destroy(entity->entity);
        toDelete.clear();

		auto camerasGroup = sceneRegistry.view<Camera, Transform>();
		auto  meshesGroup = sceneRegistry.view< Mesh , Transform>();
		auto spritesGroup = sceneRegistry.view<Sprite, Transform>();

		for (auto cameraID : camerasGroup) { LOG_SCOPE("Processing camera view");
			auto& cam = camerasGroup.get<Camera>(cameraID);

            cam.updateView();
			
			for (auto& entity : meshesGroup) {
				LOG_SCOPE("Rendering mesh");

				auto& mesh      = meshesGroup.get<   Mesh  >(entity);
				auto  transform = meshesGroup.get<Transform>(entity);

				Renderer::renderMesh(mesh, transform);
			}

			for(auto& entity : spritesGroup){
			    auto& transform = spritesGroup.get<Transform>(entity);
			    auto& sprite    = spritesGroup.get<  Sprite >(entity);

                Renderer::drawQuad2D(sprite.material.textures[0].get(), &transform, sprite.material.shader.get(), &cam, sprite.texCoords);
			}
			
		}

    }
}
