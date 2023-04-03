#include "Components/Entity.h"
#include "Components/Transform.h"

namespace PetrolEngine {
    class GameObject: public Entity {
    public:
        Transform* transform;
        
        GameObject(Entity entity): Entity(entity) {};
    };
}
