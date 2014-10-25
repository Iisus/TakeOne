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
        TEXTCOORD
    };

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        glm::vec3 tangent;
        glm::vec2 textCoord;
    };

    class Mesh
    {
    public:
        Mesh();
        ~Mesh();

        void Setup(const std::vector<Vertex>& pVertices, const std::vector<unsigned int>& pIndices, const std::bitset<5>& pAttribsUsed);
        void Render();
        void Release();
    private:
        unsigned int mVAO;
        unsigned int mVBO;
        unsigned int mIBO;

        std::vector<Vertex>         mVertices;
        std::vector<unsigned int>   mIndices;

        unsigned short mIndicesType;
        std::bitset<5> mAttribsUsed; // There are 5 VertexFormat types
    };
}