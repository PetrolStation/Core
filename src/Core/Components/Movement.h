#pragma once

#include "Static/Components/Transform.h"
#include "Static/Components/Entity.h"
#include "Static/Components/Component.h"
#include "Static/Components/Camera.h"

namespace PetrolEngine {
    class Movement: public Component {
    public:
        const float walkSpeed =  2.0f;
        const float  runSpeed = 10.0f;

        Movement(Camera* camera);

        Movement& operator=(const Movement&) { return *this; }


        void onStart() override {};
        void onUpdate() override;
    private:
        Camera* camera;
    };
}