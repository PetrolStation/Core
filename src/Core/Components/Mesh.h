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
#include "Core/Renderer/VertexBuffer.h"
#include "Vertex.h"
#include <Core/Components/MeshRenderer.h>

#include "Material.h"

#include <Core/Components/VertexData.h>

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
        {"normal"   , ShaderDataType::Float3},
        {"boneID"   , ShaderDataType::Int4},
        {"boneWeight", ShaderDataType::Float4}
    });

struct BoneInfo
{
    /*id is index in finalBoneMatrices*/
    int id;

    /*offset matrix transforms vertex from model space to bone space*/
    glm::mat4 offset;

};

    class Mesh: public Component {
    public:
        std::map<String, BoneInfo> m_BoneInfoMap; //
        int m_BoneCounter = 0;
        MeshRenderer* meshRenderer = nullptr;
        VertexLayout additionalLayout;

        void onStart() override;

        auto& GetBoneInfoMap() { return m_BoneInfoMap; }
        int& GetBoneCount() { return m_BoneCounter; } 

    public:
        Vector<     uint> indices;
        Vector<glm::vec3> vertices;
        Vector<glm::vec3> normals;
        Vector<glm::vec2> textureCoordinates;
        Vector<glm::ivec4> boneIDs;
        Vector<glm::vec4> boneWeights;

        operator MeshRenderer*() const { return meshRenderer; }
    public:
        Mesh(VertexLayout additionalLayout);
        Mesh();

        void invertFaces();
        void recalculateMesh(VertexData vertexData = {});

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
