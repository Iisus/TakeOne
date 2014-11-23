#pragma once

#include "glm/glm.hpp"
#include <vector>
#include <bitset>

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
    public:
        Mesh();
        ~Mesh();

        void Load(const std::string& pMeshFile);
        void Render();
        void Release();
    private:
        void Setup();
        unsigned int mVAO;
        unsigned int mVBO;
        unsigned int mIBO;

        unsigned short mIndicesType;

        std::vector<unsigned int>   mIndices;
        std::vector<Vertex>         mVertices;

        std::vector<unsigned int> mAttribsUsed;
    };
}
