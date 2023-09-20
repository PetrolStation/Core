#pragma once

#include <Core/Components/Component.h>
#include <Core/Components/Entity.h>
#include <Core/Scene.h>
#include "PhysicsController.h"

namespace PetrolEngine{
    
    class Collider {
    public:
        int mass;
        bool localInertia;

        Collider(int m, bool ci){
            mass = m;
            localInertia = ci;
        }
        
        ~Collider() {};
    };

    // Component for use in ECS
    class PlaneCollider: public Collider, public Component {
    public:
        PlaneCollider(int m, bool ci) : Collider(m, ci) {};
        PlaneCollider() : Collider(0, false) {
        }

        void onStart () {
            component = entity->getScene()->getEntityByComponent<PhysicsController>()->getComponent<PhysicsController>().newPlaneCollider();
            *component = *(Component*)this; // copy information about parent to the collider
            component->onStart ();
        }
        void onUpdate() { component->onUpdate(); }

    private:
        Component* component;
    };

    class MeshCollider: public Collider, public Component {
    public:
        MeshCollider(int m, bool ci) : Collider(m, ci) {
        };

        void onStart () {
            component = entity->getScene()->getEntityByComponent<PhysicsController>()->getComponent<PhysicsController>().newMeshCollider(mass, localInertia);
            *component = *(Component*)this; // copy information about parent to the collider
            component->onStart ();
        }
        void onUpdate() { component->onUpdate(); }

    private:
        Component* component;
    };

    class BoxCollider: public Collider, public Component {
    public:
        BoxCollider(int m, bool ci) : Collider(m, ci) {
        }

        void onStart () {
            component = entity->getScene()->getEntityByComponent<PhysicsController>()->getComponent<PhysicsController>().newBoxCollider(mass, localInertia);
            *component = *(Component*)this; // copy information about parent to the collider
            component->onStart ();
        }
        void onUpdate() { component->onUpdate(); }

        ~BoxCollider() { delete component; }
        
    private:
        Component* component;
    };
}
