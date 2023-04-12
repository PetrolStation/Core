#pragma once

#include "Core/Components/Component.h"
#include "Core/Components/Material.h"
#include <Core/Renderer/IndexBuffer.h>
#include <Core/Renderer/VertexBuffer.h>
#include <Core/Renderer/VertexArray.h>

namespace PetrolEngine {
    class MeshRenderer: public Component {
    public:
        Ref<VertexArray> vertexArray;
        Material material;
    };
}
