#pragma once

#include "glm/glm.hpp"
#include <vector>
#include <string>

namespace TakeOne
{
    enum class VertexFormat : unsigned int
    {
        POSITION,
        NORMAL,
        COLOR,
        TEXCOORD,

        Count
    };

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        glm::vec2 texCoord;
    };

    class Mesh
    {
    friend class RenderObject;

    public:
        Mesh();
        ~Mesh();

        void Render();
        void Release();

    protected:
        //accessed from RenderObject
        void SetVertices(std::vector<Vertex> pVertices) { mVertices = std::move(pVertices); }
        void SetIndices(std::vector<unsigned int> pIndices) { mIndices = std::move(pIndices); }
        void SetAttribsUsed(std::vector<unsigned int> pAttribsUsed) { mAttribsUsed = std::move(pAttribsUsed); }

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
