#pragma once

#include "Core/Components/Properties.h"
#include "Core/DebugTools.h"
#include "entt/entt.hpp"
#include "Core/Scene.h"
#include <iostream>
#include "Component.h"

namespace PetrolEngine {

    class SystemManager {
    public:
        bool started = false;
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
            static bool registered = false;

            if(registered) return;

            systemUpdates.push_back(systemUpdate<T>);
            systemStarts .push_back(systemStart <T>);

            registered = true;
        }

        void update() { LOG_FUNCTION();
            for(auto& system : systemUpdates) system(scene);
        }
        void start () { LOG_FUNCTION();
            if(started) return;

            started = true;

            for(int i = 0; i < systemStarts.size(); i++) systemStarts[i](scene);
        }
    };
   
	class Entity {
	public:
        String name;
	    static Set<entt::id_type> componentTypes;

		template<typename T, typename ... Args>
		T& addComponent(Args&&... args) {
            auto typeId = entt::type_hash<T>::value();
            auto& component = scene->sceneRegistry.emplace<T>(entity, std::forward<Args>(args)...);
            component.entity = this;
            
            componentTypes.insert(typeId);

            if constexpr (std::is_base_of_v<InternalComponent, T>)
                component.typeId = typeId;

            if constexpr (std::is_base_of_v<Component, T>) {
                scene->systemManager->template registerSystem<T>();
                component.transform = &getComponent<Transform>();
                if(scene->isStarted()) component.onStart();
            }

            return component;
		}

        // adds component of type T to this entity and returns reference to it
        template<typename T>
        T& getComponent() {
            return scene->sceneRegistry.get<T>(entity);
        }

        void destroy(){
            std::cout<<this->getComponent<Properties>().name<<" - make me  crazy\n";
            bool found = false;
            for(int i=0;i<scene->toDelete.size();i++){
                if(scene->toDelete[i] == this) found = true;
            }
            if(found == false) scene->toDelete.push_back(this);
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

        Entity* parent = nullptr;
        Vector<Entity*> children;
	private:
        // Entity should be created only by Scene class
        explicit Entity(entt::entity entity = entt::null, Scene* scene = nullptr, String name = "Entity");

        entt::entity entity { entt::null };
		Scene*       scene  {   nullptr  };

        friend class Scene;
        friend class GameObject;
	};

} 
