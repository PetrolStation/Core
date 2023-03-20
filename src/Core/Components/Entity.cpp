#include "PCH.h"

#include "Core/Components/Entity.h"
#include "Core/Scene.h"

namespace PetrolEngine {
    Entity::Entity(entt::entity entity, Scene* scene): entity(entity), scene(scene) {};

    uint   Entity::getID   () { return (uint) entity; }
	Scene* Entity::getScene() { return        scene ; }
	bool Entity::isValid() {
		return !(entity == entt::null);
	}

}