#pragma once

#include "entt/entt.hpp"
#include "Core/Scene.h"

#include "Component.h"

namespace PetrolEngine {

    class SystemManager {
    public:
        Scene* scene = nullptr;

        Vector<void(*)(Scene*)> systemUpdates;
        Vector<void(*)(Scene*)> systemStarts;

        template<typename T>
        static void systemUpdate(Scene* scene) {
            if constexpr (std::is_base_of_v<Component, T>) {
                auto group = scene->sceneRegistry.view<T>();

                for (auto &entity: group) {
                    group.template get<T>(entity).onUpdate();
                }
            }
        }

        template<typename T>
        static void systemStart(Scene* scene) {
            if constexpr (std::is_base_of_v<Component, T>) {
                auto group = scene->sceneRegistry.view<T>();

                for (auto &entity: group) {
                    group.template get<T>(entity).onStart();
                }
            }
        }

        template<typename T>
        void registerSystem() {
            systemUpdates.push_back(systemUpdate<T>);
            systemStarts .push_back(systemStart <T>);
        }

        void update() { for(auto& system : systemUpdates) system(scene); }
        void start () { for(auto& system : systemStarts ) system(scene); }
    };
    
	class Entity {
	public:
		template<typename T, typename ... Args>
		T& addComponent(Args&&... args) {
            auto& c = scene->sceneRegistry.emplace<T>(entity, std::forward<Args>(args)...);
            c.entity = this;

            if constexpr (std::is_base_of_v<Component, T>) {
                scene->systemManager->template registerSystem<T>();
                c.transform = &getComponent<Transform>();
            }

            return c;
		}

        // adds component of type T to this entity and returns reference to it
        template<typename T>
        T& getComponent() {
            return scene->sceneRegistry.get<T>(entity);
        }

        // returns how many components of type T are attached to this entity (can be used as bool)
		template<typename T>
		int hasComponent() {
			return scene->sceneRegistry.all_of<T>(entity);
		}

		template<typename T>
		void removeComponent() {
            //scene->sceneRegistry.remove_if_exists<T>(entity);
		}

		uint   getID();
		Scene* getScene();
		bool isValid();

	private:
        // Entity should be created only by Scene class
        explicit Entity(entt::entity entity = entt::null, Scene* scene = nullptr);

        entt::entity entity { entt::null };
		Scene*       scene  {   nullptr  };

        friend class Scene;
	};

} 
