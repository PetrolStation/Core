#pragma once

//#include "Core/Physics/Collider.h"
#include <Core/Components/Component.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace PetrolEngine {
    class Collider2DApi: public Component{
      public:
        int mass = 0;
        bool localInertia = false;
        bool sensor = false;
        virtual void applyForce(glm::vec2 force) = 0;
        virtual void setLinearVelocity(glm::vec2 vel) = 0;
        virtual glm::vec2 getLinearVelocity() = 0;
        virtual glm::vec2 getLinearVelocityFromWorldPoint(glm::vec2 point) = 0;
        virtual void setTransform(glm::vec2 pos, float angle) = 0;

        //virtual ~Collider2DApi() = default;
    };

    class Collider3DApi: public Component{
      public:
        int mass = 0;
        bool localInertia = false;
        bool sensor = false;
        virtual void applyForce(glm::vec3 force) = 0;
    };
}
