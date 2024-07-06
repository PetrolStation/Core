#pragma once

#include <Core/Components/Component.h>
#include <Core/Components/Entity.h>
#include <Core/Scene.h>
#include <cstring>
#include "Core/Components/Properties.h"
#include "Core/Physics/ColliderApi.h"
#include "PhysicsController.h"

namespace PetrolEngine{
    
    class Collider3D: public Component {
    public:
        void applyForce(glm::vec3 force) {collider->applyForce(force);};
        
        void onStart() {
            collider = newShape();
            *(Component*)collider = *(Component*)this; // copy information about parent to the collider
            collider->onStart ();
        }
        void onUpdate(){collider->onUpdate();}

        virtual Collider3DApi* newShape() = 0;
        //virtual ~Collider3D() = 0;

    protected:
        Collider3DApi* collider;
        int mass = 0;
        bool localInertia = false;
    };

    // Component for use in ECS
    class PlaneCollider3D: public Collider3D {
    public:
        PlaneCollider3D(int m, bool ci) {this->mass = m; this->localInertia = ci;};
        PlaneCollider3D() { this->mass = 0; this->localInertia = false; }

        Collider3DApi* newShape() {
            return entity->getScene()->getEntityByComponent<PhysicsController3D>()->getComponent<PhysicsController3D>().newPlaneCollider();
        }
    };

    class MeshCollider3D: public Collider3D {
    public:
        MeshCollider3D(int m, bool ci) {this->mass = m; this->localInertia = ci;};
        Collider3DApi* newShape() {
            return entity->getScene()->getEntityByComponent<PhysicsController3D>()->getComponent<PhysicsController3D>().newMeshCollider(mass, localInertia);
        }
    };

    class BoxCollider3D: public Collider3D {
    public:
        BoxCollider3D(int m, bool ci) {this->mass = m; this->localInertia = ci;};
        BoxCollider3D() = default;
        
        Collider3DApi* newShape() {
            return entity->getScene()->getEntityByComponent<PhysicsController3D>()->getComponent<PhysicsController3D>().newBoxCollider(mass, localInertia);
        }

        ~BoxCollider3D() { }
       
        //Collider* operator->(){
        //    return (Collider*)component;
        //}

    };

    //
    // 2DDDDD
    //

    class Collider2D: public Component {
    public:
        void applyForce(glm::vec2 force) {collider->applyForce(force);};
        void setLinearVelocity(glm::vec2 vel) {collider->setLinearVelocity(vel);}
        void setTransform(glm::vec2 pos, float angle) {collider->setTransform(pos, angle);}

        glm::vec2 getLinearVelocityFromWorldPoint(glm::vec2 point= {0,0}){return collider->getLinearVelocityFromWorldPoint(point);}
        glm::vec2 getLinearVelocity() {return collider->getLinearVelocity();}
        
        void onStart() {
            collider = newShape();
            collider->entity = this->entity;
            collider->transform = this->transform;
            //*(Component*)collider = *(Component*)this; // copy information about parent to the collider
            collider->onStart ();
        }
        void onUpdate(){collider->onUpdate();}

        virtual Collider2DApi* newShape() = 0;
        ~Collider2D(){
            //std::cout<<this->entity->getComponent<Properties>().name<<"\n";
            delete collider;
        }

    protected:
        Collider2DApi* collider = nullptr;
        int mass = 0;
        bool localInertia = false;
        bool sensor = false;
    };

    // Component for use in ECS
    class PlaneCollider2D: public Collider2D {
    public:
        PlaneCollider2D(int m, bool ci) {this->mass = m; this->localInertia = ci;};
        PlaneCollider2D(){ this->mass = 0; this->localInertia = false; }

        Collider2DApi* newShape() {
            return entity->getScene()->getEntityByComponent<PhysicsController2D>()->getComponent<PhysicsController2D>().newPlaneCollider();
        }
    };

    class MeshCollider2D: public Collider2D {
    public:
        MeshCollider2D(int m, bool ci) {this->mass = m; this->localInertia = ci;};
        Collider2DApi* newShape() {
            return entity->getScene()->getEntityByComponent<PhysicsController2D>()->getComponent<PhysicsController2D>().newMeshCollider(mass, localInertia);
        }
    };

    class BoxCollider2D: public Collider2D {
    public:
        BoxCollider2D(int m, bool ci, bool sensor = false) {this->mass = m; this->localInertia = ci;this->sensor = sensor;};
        
        Collider2DApi* newShape() {
            return entity->getScene()->getEntityByComponent<PhysicsController2D>()->getComponent<PhysicsController2D>().newBoxCollider(mass, localInertia, sensor);
        }

//        ~BoxCollider2D(){}
       
        //Collider* operator->(){
        //    return (Collider*)component;
        //}

    };

}
