#pragma once

#include "Core/Components/Component.h"
#include "Core/Components/Material.h"
#include <Static/Renderer/defaultShaders.h>

namespace PetrolEngine{

    class Sprite: public Component {
    public:
        Material material;
        glm::vec4 texCoords = {0,0,1,1};

        Sprite(Material m, glm::vec4 c = {0,0,1,1}): material(m), texCoords(c) {}
    };
}
