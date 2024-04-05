#pragma once

// ! This class can be used only using StaticRenderer context.

// TODO: raw pointers
#include <Core/Aliases.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Core/Renderer/VertexArray.h"

#include "Core/Components/Component.h"
#include "Vertex.h"
#include <Core/Components/MeshRenderer.h>

#include "Material.h"

/*
 * TODO:
 *  - switch to raw pointers
 *  - add physix
 *  - add networking
 *  - add lighting
 *
 *  - repair vulkan
 *  - add animation
 */

namespace PetrolEngine {

    const VertexLayout standardLayout = VertexLayout({
        {"position" , ShaderDataType::Float3},
        {"texCords" , ShaderDataType::Float2},
        {"normal"   , ShaderDataType::Float3}
    });

    class Mesh: public Component {
    public:
        MeshRenderer* meshRenderer = nullptr;
        VertexLayout additionalLayout;

        void onStart() override;

    public:
        Vector<     uint> indices;
        Vector<glm::vec3> vertices;
        Vector<glm::vec3> normals;
        Vector<glm::vec2> textureCoordinates;

        operator MeshRenderer*() const { return meshRenderer; }
    public:
        Mesh(VertexLayout additionalLayout);
        Mesh();

        void invertFaces();
        void recalculateMesh(void* additionalData=nullptr, int64 additionalDataSize=0);

        NO_DISCARD
        Ref<VertexArray> getVertexArray() const { return this->meshRenderer->vertexArray; } 

		Mesh(
			const Vector<glm::vec3>& vertices,
			const Vector<     uint>& indices,
			Material                 material = {},
			VertexLayout             layout = VertexLayout({
				{"position" , ShaderDataType::Float3},
				{"texCords" , ShaderDataType::Float2},
				{"normal"   , ShaderDataType::Float3},
				{"tangent"  , ShaderDataType::Float3},
				{"bitangent", ShaderDataType::Float3}
            })
		);

		~Mesh() = default;
	};

    Mesh createCube(float size = 2.0f);
}
