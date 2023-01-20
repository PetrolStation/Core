#pragma once

#include "Static/Window/Window.h"

#include "Static/Components/Component.h"
#include "Static/Components/Transform.h"

namespace PetrolEngine {
    class TestRotationScript : public Component {
    public:
        void onUpdate() override {
            transform->rotateY( (float) deltaTime );
        }
    };
}