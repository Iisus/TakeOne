#include "BoxRenderObject.h"
#define UNIT 1.0f

TakeOne::BoxRenderObject::BoxRenderObject(const std::shared_ptr<Program>& pProgram) :
    RenderObject(pProgram)
{
    std::vector<unsigned int> attribsUsed(Vertex::Count);
    attribsUsed[Vertex::POSITION] = 1;
    attribsUsed[Vertex::NORMAL] = 0;
    attribsUsed[Vertex::COLOR] = 1;
    attribsUsed[Vertex::TEXCOORD] = 1;

    mMesh->SetAttribsUsed(std::move(attribsUsed));

    std::vector<Vertex> vertices
    {
        Vertex(glm::vec3(-UNIT, -UNIT, -UNIT), glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3( UNIT, -UNIT, -UNIT), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3( UNIT,  UNIT, -UNIT), glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
        Vertex(glm::vec3(-UNIT,  UNIT, -UNIT), glm::vec3(0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)),
        Vertex(glm::vec3(-UNIT, -UNIT,  UNIT), glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3( UNIT, -UNIT,  UNIT), glm::vec3(0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3( UNIT,  UNIT,  UNIT), glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
        Vertex(glm::vec3(-UNIT,  UNIT,  UNIT), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)),
    };

    mMesh->SetVertices(std::move(vertices));

    std::vector<unsigned int> indices
    {
        0,2,1,
        0,3,2,

        1,2,6,
        6,5,1,

        4,5,6,
        6,7,4,

        2,3,6,
        6,3,7,

        0,7,3,
        0,4,7,

        0,1,5,
        0,5,4
    };

    mMesh->SetIndices(std::move(indices));

    mMesh->Setup();
}
