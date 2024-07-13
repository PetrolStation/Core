#include "PCH.h"

#include "Mesh.h"

#include "Core/Components/Vertex.h"
#include <Static/Renderer/Renderer.h>
#include <Core/Components/Entity.h>

namespace PetrolEngine {
    Mesh::Mesh(VertexLayout additionalLayout) {
        /*
        this->material         = Material();
        this->additionalLayout = additionalLayout;

        LOG("ADDITONAL LAYOUT: mesh", 3);

        auto vertexBufferS = Renderer::newVertexBuffer(  standardLayout);
        auto vertexBufferE = Renderer::newVertexBuffer(additionalLayout);
        auto indexBuffer   = Renderer::newIndexBuffer ();

        this->vertexArray = Renderer::createVertexArray();

        this->vertexArray->addVertexBuffer(vertexBufferS);
        this->vertexArray->addVertexBuffer(vertexBufferE);
        this->vertexArray-> setIndexBuffer( indexBuffer );
        */

        this->meshRenderer = new MeshRenderer();
        
        recalculateMesh();
    }

    void Mesh::onStart() {
        this->meshRenderer = &this->entity->addComponent<MeshRenderer>(*this->meshRenderer);
    }

    Mesh::Mesh() {
        this->meshRenderer = new MeshRenderer();
    }

    Mesh::Mesh(
            const Vector<glm::vec3>& vertices,
            const Vector<     uint>& indices ,
            Material                 material,
            VertexLayout             additionalData) {
        this->vertices = vertices;
        this->indices  = indices;

        this->meshRenderer = new MeshRenderer();
        this->meshRenderer->material = material;

        recalculateMesh();
    }

    void Mesh::recalculateMesh(VertexData adVertexData) {
        this->meshRenderer->vertexArray = Renderer::createVertexArray();

        auto vertexBufferS = Renderer::newVertexBuffer(standardLayout);
        auto indexBuffer   = Renderer::newIndexBuffer ();

        uint64 vertexCount = 0;

        if(vertices          .size() > vertexCount) vertexCount = vertices          .size();
        if(normals           .size() > vertexCount) vertexCount = normals           .size();
        if(textureCoordinates.size() > vertexCount) vertexCount = textureCoordinates.size();

        VertexData vertexData;

        vertexData.changeLayout(standardLayout);
        vertexData.resize(vertexCount);

        for(int i = 0; i < vertices          .size(); i++) vertexData[i]["position"  ] = vertices[i];
        for(int i = 0; i < normals           .size(); i++) vertexData[i]["normal"    ] = normals [i];
        for(int i = 0; i < textureCoordinates.size(); i++) vertexData[i]["texCords"  ] = textureCoordinates[i];
        for(int i = 0; i < boneIDs           .size(); i++) vertexData[i]["boneID"    ] = boneIDs [i];
        for(int i = 0; i < boneWeights       .size(); i++) vertexData[i]["boneWeight"] = boneWeights [i];

        vertexBufferS->setData(vertexData.data, (int64) vertexCount    * (int64) vertexData.elementSize);
        indexBuffer  ->setData(indices.data() , (int64) indices.size() * (int64) sizeof(uint));

        this->meshRenderer->vertexArray-> setIndexBuffer( indexBuffer );
        this->meshRenderer->vertexArray->addVertexBuffer(vertexBufferS);

        if(adVertexData.elementCount != 0){
            auto vertexBufferE = Renderer::newVertexBuffer(additionalLayout);

            vertexBufferE->setData(adVertexData.data, (int64) vertexCount    * (int64) adVertexData.elementSize);

            this->meshRenderer->vertexArray->addVertexBuffer(vertexBufferE);
        }


    }

    void Mesh::invertFaces() {
        for(int i = 0; i < indices.size(); i += 3)
            swap(indices[i], indices[i + 2]);
    }

    Mesh createCube(float size) {
        float d = size / 2.0f;
        return Mesh({
            // front
            {-d, -d, d},
            { d, -d, d},
            { d,  d, d},
            {-d,  d, d},
            // back
            {-d, -d, -d},
            { d, -d, -d},
            { d,  d, -d},
            {-d,  d, -d}
        }, {
                0, 1, 2, 2, 3, 0, // front
                1, 5, 6, 6, 2, 1, // right
                7, 6, 5, 5, 4, 7, // back
                4, 0, 3, 3, 7, 4, // left
                4, 5, 1, 1, 0, 4, // bottom
                3, 2, 6, 6, 7, 3  // top
        });
    }
}
