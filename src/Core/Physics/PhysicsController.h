#pragma once

#include <PCH.h>

#include "ColliderApi.h"
#include <Core/Components/Component.h>

namespace PetrolEngine{
    
    class PhysicsCreator {
    public:
        virtual Component* newPlaneCollider(int mass, bool localInertia, glm::vec3 inertia) = 0;
        virtual Component*  newMeshCollider(int mass, bool localInertia, glm::vec3 inertia) = 0;
        virtual Component*   newBoxCollider(int mass, bool localInertia, glm::vec3 inertia) = 0;

        virtual Component* newPhysicsController() = 0;
    };

    class PhysicsController: public Component {
    public:
        Vector<Component*> colliders;
        
        template<typename T>
        PhysicsController(                       ){ this->creator = new T(); component = creator->newPhysicsController(); }
        PhysicsController(PhysicsCreator* creator){ this->creator = creator; component = creator->newPhysicsController(); }

        ~PhysicsController() {
            for (auto& collider : colliders) delete collider;
            delete this->component;
        }

        void onStart () { *component = *(Component*)this; component->onStart (); }
        void onUpdate() {                                 component->onUpdate(); }

        Component* newPlaneCollider(int m = 1, bool li = false, glm::vec3 i = {0,0,0}) { return colliders.emplace_back(creator->newPlaneCollider(m, li, i)); }
        Component*  newMeshCollider(int m = 1, bool li = true , glm::vec3 i = {1,1,1}) { return colliders.emplace_back(creator->newMeshCollider (m, li, i)); }
        Component*   newBoxCollider(int m = 1, bool li = true , glm::vec3 i = {1,1,1}) { return colliders.emplace_back(creator->newBoxCollider  (m, li, i)); }
    private:
        PhysicsCreator* creator;

    public:
        Component* component;
    };
}
