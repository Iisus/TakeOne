#include "BoxRenderObject.h"
#define UNIT 1.0f

TakeOne::BoxRenderObject::BoxRenderObject(const std::shared_ptr<Program>& pProgram) :
    RenderObject(pProgram)
{
    std::vector<unsigned int> attribsUsed(Vertex::Count);
    attribsUsed[Vertex::POSITION] = 1;
    attribsUsed[Vertex::NORMAL] = 1;
    attribsUsed[Vertex::COLOR] = 0;
    attribsUsed[Vertex::TEXCOORD] = 1;

    mMesh->SetAttribsUsed(std::move(attribsUsed));

    std::vector<Vertex> vertices
    {
        Vertex(glm::vec3( UNIT, -UNIT, -UNIT), glm::vec3( 0.0, -1.0,  0.0), glm::vec3(0.0), glm::vec2( 0.0,  0.0)),
        Vertex(glm::vec3( UNIT, -UNIT,  UNIT), glm::vec3( 0.0, -1.0,  0.0), glm::vec3(0.0), glm::vec2( 1.0,  0.0)),
        Vertex(glm::vec3(-UNIT, -UNIT,  UNIT), glm::vec3( 0.0, -1.0,  0.0), glm::vec3(0.0), glm::vec2( 1.0,  1.0)),
        Vertex(glm::vec3(-UNIT, -UNIT, -UNIT), glm::vec3( 0.0, -1.0,  0.0), glm::vec3(0.0), glm::vec2( 0.0,  1.0)),
        Vertex(glm::vec3( UNIT,  UNIT, -UNIT), glm::vec3( 0.0,  1.0,  0.0), glm::vec3(0.0), glm::vec2( 0.0,  0.0)),
        Vertex(glm::vec3(-UNIT,  UNIT, -UNIT), glm::vec3( 0.0,  1.0,  0.0), glm::vec3(0.0), glm::vec2( 1.0,  0.0)),
        Vertex(glm::vec3(-UNIT,  UNIT,  UNIT), glm::vec3( 0.0,  1.0,  0.0), glm::vec3(0.0), glm::vec2( 1.0,  1.0)),
        Vertex(glm::vec3( UNIT,  UNIT,  UNIT), glm::vec3( 0.0,  1.0,  0.0), glm::vec3(0.0), glm::vec2( 0.0,  1.0)),
        Vertex(glm::vec3( UNIT, -UNIT, -UNIT), glm::vec3( 1.0,  0.0,  0.0), glm::vec3(0.0), glm::vec2( 0.0,  0.0)),
        Vertex(glm::vec3( UNIT,  UNIT, -UNIT), glm::vec3( 1.0,  0.0,  0.0), glm::vec3(0.0), glm::vec2( 1.0,  0.0)),
        Vertex(glm::vec3( UNIT,  UNIT,  UNIT), glm::vec3( 1.0,  0.0,  0.0), glm::vec3(0.0), glm::vec2( 1.0,  1.0)),
        Vertex(glm::vec3( UNIT, -UNIT,  UNIT), glm::vec3( 1.0,  0.0,  0.0), glm::vec3(0.0), glm::vec2( 0.0,  1.0)),
        Vertex(glm::vec3( UNIT, -UNIT,  UNIT), glm::vec3(-0.0, -0.0,  1.0), glm::vec3(0.0), glm::vec2( 0.0,  0.0)),
        Vertex(glm::vec3( UNIT,  UNIT,  UNIT), glm::vec3(-0.0, -0.0,  1.0), glm::vec3(0.0), glm::vec2( 1.0,  0.0)),
        Vertex(glm::vec3(-UNIT,  UNIT,  UNIT), glm::vec3(-0.0, -0.0,  1.0), glm::vec3(0.0), glm::vec2( 1.0,  1.0)),
        Vertex(glm::vec3(-UNIT, -UNIT,  UNIT), glm::vec3(-0.0, -0.0,  1.0), glm::vec3(0.0), glm::vec2( 0.0,  1.0)),
        Vertex(glm::vec3(-UNIT, -UNIT,  UNIT), glm::vec3(-1.0, -0.0, -0.0), glm::vec3(0.0), glm::vec2( 0.0,  0.0)),
        Vertex(glm::vec3(-UNIT,  UNIT,  UNIT), glm::vec3(-1.0, -0.0, -0.0), glm::vec3(0.0), glm::vec2( 1.0,  0.0)),
        Vertex(glm::vec3(-UNIT,  UNIT, -UNIT), glm::vec3(-1.0, -0.0, -0.0), glm::vec3(0.0), glm::vec2( 1.0,  1.0)),
        Vertex(glm::vec3(-UNIT, -UNIT, -UNIT), glm::vec3(-1.0, -0.0, -0.0), glm::vec3(0.0), glm::vec2( 0.0,  1.0)),
        Vertex(glm::vec3( UNIT,  UNIT, -UNIT), glm::vec3( 0.0,  0.0, -1.0), glm::vec3(0.0), glm::vec2( 0.0,  0.0)),
        Vertex(glm::vec3( UNIT, -UNIT, -UNIT), glm::vec3( 0.0,  0.0, -1.0), glm::vec3(0.0), glm::vec2( 1.0,  0.0)),
        Vertex(glm::vec3(-UNIT, -UNIT, -UNIT), glm::vec3( 0.0,  0.0, -1.0), glm::vec3(0.0), glm::vec2( 1.0,  1.0)),
        Vertex(glm::vec3(-UNIT,  UNIT, -UNIT), glm::vec3( 0.0,  0.0, -1.0), glm::vec3(0.0), glm::vec2( 0.0,  1.0))
    };

    mMesh->SetVertices(std::move(vertices));

    std::vector<unsigned int> indices
    {
        0, 1, 2,
        0, 2, 3,

        4, 5, 6,
        4, 6, 7,

        8, 9, 10,
        8, 10, 11,

        12, 13, 14,
        12, 14, 15,

        16, 17, 18,
        16, 18, 19,

        20, 21, 22,
        20, 22, 23
    };

    mMesh->SetIndices(std::move(indices));

    mMesh->Setup();
}
