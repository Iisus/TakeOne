#pragma once

#include <vector>
#include <bitset>
#include "glm/glm.hpp"

namespace TakeOne
{

    enum class VertexFormat : unsigned int
    {
        POSITION,
        NORMAL,
        COLOR,
        TANGENT,
        TEXCOORD,

        Count
    };

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        glm::vec3 tangent;
        glm::vec2 texCoord;
    };

    class Mesh
    {
    public:
        Mesh();
        ~Mesh();

        void Setup(const std::vector<Vertex>& pVertices, const std::vector<unsigned int>& pIndices, const std::bitset<(unsigned int)VertexFormat::Count>& pAttribsUsed);
        void Render();
        void Release();
    private:
        unsigned int mVAO;
        unsigned int mVBO;
        unsigned int mIBO;

        std::vector<Vertex>         mVertices;
        std::vector<unsigned int>   mIndices;

        unsigned short mIndicesType;
        std::bitset<(unsigned int)VertexFormat::Count> mAttribsUsed; // There are 5 VertexFormat types
    };
}