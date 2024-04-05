#include "Components/Entity.h"
#include "Components/Transform.h"

namespace PetrolEngine {
    class GameObject: public Entity {
    public:
        Transform* transform;
        
        explicit GameObject(entt::entity entity = entt::null, Scene* scene = nullptr, String name = "GameObject"): Entity(entity, scene, name) {};
    };
}
