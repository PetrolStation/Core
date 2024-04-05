#pragma once

#include <Core/Components/Component.h>
#include <Core/Aliases.h>

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

// TODO: make camera rotation work

namespace PetrolEngine {
    class Camera: public Component {
    public:
        glm::ivec2 resolution = glm::ivec2(1280, 720);

        [[Expose]] [[Serialize]] float zoom  =  60.0f;
        [[Expose]] [[Serialize]] float near_ =   0.1f; // near and far are reserved words in msvc
        [[Expose]] [[Serialize]] float far_  = 500.0f;

        Camera();

        void updatePerspective();
        void updateView();

        NO_DISCARD const glm::mat4& getViewMatrix () const { return view       ; };
        NO_DISCARD const glm::mat4& getPerspective() const { return perspective; };
    private:
        glm::mat4 perspective = glm::mat4(1.0f);
        glm::mat4 view        = glm::mat4(1.0f);
    };
}
