#pragma once

#include "glm/glm.hpp"
#include <vector>
#include <string>

namespace TakeOne
{
    struct Vertex
    {
        Vertex(){}
        Vertex(glm::vec3 _position, glm::vec3 _normal, glm::vec3 _color, glm::vec2 _texCoord) :
            position(_position), normal(_normal), color(_color), texCoord(_texCoord)
        { }

        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        glm::vec2 texCoord;

        enum VertexFormat : unsigned int
        {
            POSITION,
            NORMAL,
            COLOR,
            TEXCOORD,

            Count
        };
    };

    class Mesh
    {
    public:
        Mesh();
        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;
        Mesh(Mesh&&);
        Mesh& operator=(Mesh&&);
        ~Mesh();

        void Render();
        void Release();

        void SetVertices(std::vector<Vertex>&& pVertices) { mVertices = std::move(pVertices); }
        void SetIndices(std::vector<unsigned int>&& pIndices) { mIndices = std::move(pIndices); }
        void SetAttribsUsed(std::vector<unsigned int>&& pAttribsUsed) { mAttribsUsed = std::move(pAttribsUsed); }

        void Setup();

    private:
        unsigned int mVAO;
        unsigned int mVBO;
        unsigned int mIBO;

        unsigned short mIndicesType;

        std::vector<unsigned int>   mIndices;
        std::vector<Vertex>         mVertices;

        std::vector<unsigned int> mAttribsUsed;
    };
}
