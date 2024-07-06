#pragma once

#include <PCH.h>

#include "ColliderApi.h"
#include <Core/Components/Component.h>

namespace PetrolEngine{
    
    class PhysicsCreator3D {
    public:
        virtual Collider3DApi* newPlaneCollider(int mass, bool localInertia, glm::vec3 inertia) = 0;
        virtual Collider3DApi*  newMeshCollider(int mass, bool localInertia, glm::vec3 inertia) = 0;
        virtual Collider3DApi*   newBoxCollider(int mass, bool localInertia, glm::vec3 inertia) = 0;

        virtual Component* newPhysicsController() = 0;
    };

    class PhysicsController3D: public Component {
    public:
        Vector<Collider3DApi*> colliders;
        
        template<typename T>
        PhysicsController3D(                         ){ this->creator = new T(); component = creator->newPhysicsController(); }
        PhysicsController3D(PhysicsCreator3D* creator){ this->creator = creator; component = creator->newPhysicsController(); }
        PhysicsController3D() = default;
        ~PhysicsController3D() {
            for (auto& collider : colliders) delete collider;
            delete this->component;
        }

        void onStart () { *component = *(Component*)this; component->onStart (); }
        void onUpdate() {                                 component->onUpdate(); }

        Collider3DApi* newPlaneCollider(int m = 1, bool li = false, glm::vec3 i = {0,0,0}) { return colliders.emplace_back(creator->newPlaneCollider(m, li, i)); }
        Collider3DApi*  newMeshCollider(int m = 1, bool li = true , glm::vec3 i = {1,1,1}) { return colliders.emplace_back(creator->newMeshCollider (m, li, i)); }
        Collider3DApi*   newBoxCollider(int m = 1, bool li = true , glm::vec3 i = {1,1,1}) { return colliders.emplace_back(creator->newBoxCollider  (m, li, i)); }
    private:
        PhysicsCreator3D* creator;

    public:
        Component* component;
    };

    class PhysicsCreator2D {
    public:
        virtual Collider2DApi* newPlaneCollider(int mass, bool localInertia, bool sensor) = 0;
        virtual Collider2DApi*  newMeshCollider(int mass, bool localInertia, bool sensor) = 0;
        virtual Collider2DApi*   newBoxCollider(int mass, bool localInertia, bool sensor) = 0;

        virtual Component* newPhysicsController() = 0;
    };

    class PhysicsController2D: public Component {
    public:
        Vector<Collider2DApi*> colliders;
        
        template<typename T>
        PhysicsController2D(                         ){ this->creator = new T(); component = creator->newPhysicsController(); }
        PhysicsController2D(PhysicsCreator2D* creator){ this->creator = creator; component = creator->newPhysicsController(); }

        ~PhysicsController2D() {
            //for (auto& collider : colliders) delete collider;
            delete this->component;
        }

        void onStart () { *component = *(Component*)this; component->onStart (); }
        void onUpdate() {                                 component->onUpdate(); }

        Collider2DApi* newPlaneCollider(int m = 1, bool li = false, bool sensor = false) { return colliders.emplace_back(creator->newPlaneCollider(m, li, sensor)); }
        Collider2DApi*  newMeshCollider(int m = 1, bool li = true , bool sensor = false) { return colliders.emplace_back(creator->newMeshCollider (m, li, sensor)); }
        Collider2DApi*   newBoxCollider(int m = 1, bool li = true , bool sensor = false) { return colliders.emplace_back(creator->newBoxCollider  (m, li, sensor)); }
    private:
        PhysicsCreator2D* creator;

    public:
        Component* component;
    };

}
