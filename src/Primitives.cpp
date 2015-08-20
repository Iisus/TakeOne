#include "Primitives.h"
#include <glm/gtx/constants.hpp>

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

TakeOne::PlaneRenderObject::PlaneRenderObject(const std::shared_ptr<Program>& pProgram) :
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
        Vertex(glm::vec3( UNIT, -UNIT,  UNIT), glm::vec3(-0.0, -0.0,  1.0), glm::vec3(0.0), glm::vec2( 0.0,  0.0)),
        Vertex(glm::vec3( UNIT,  UNIT,  UNIT), glm::vec3(-0.0, -0.0,  1.0), glm::vec3(0.0), glm::vec2( 1.0,  0.0)),
        Vertex(glm::vec3(-UNIT,  UNIT,  UNIT), glm::vec3(-0.0, -0.0,  1.0), glm::vec3(0.0), glm::vec2( 1.0,  1.0)),
        Vertex(glm::vec3(-UNIT, -UNIT,  UNIT), glm::vec3(-0.0, -0.0,  1.0), glm::vec3(0.0), glm::vec2( 0.0,  1.0)),
    };

    mMesh->SetVertices(std::move(vertices));

    std::vector<unsigned int> indices
    {
        0, 1, 2,
        0, 2, 3,
    };

    mMesh->SetIndices(std::move(indices));

    mMesh->Setup();
}

TakeOne::SphereRenderObject::SphereRenderObject(const std::shared_ptr<Program>& pProgram, float pRadius, int pRings, int pSectors) :
    RenderObject(pProgram)
{

    std::vector<unsigned int> attribsUsed(Vertex::Count);
    attribsUsed[Vertex::POSITION] = 1;
    attribsUsed[Vertex::NORMAL] = 1;
    attribsUsed[Vertex::COLOR] = 0;
    attribsUsed[Vertex::TEXCOORD] = 1;

    mMesh->SetAttribsUsed(std::move(attribsUsed));

    std::vector<Vertex> vertices;
    vertices.resize(pRings * pSectors);

    float const R = 1./(float)(pRings-1);
    float const S = 1./(float)(pSectors-1);
    int r, s;

    std::vector<Vertex>::iterator v = vertices.begin();

    for(r = 0; r < pRings; r++) for(s = 0; s < pSectors; s++)
    {
        float const y = sin( -glm::half_pi<float>() + glm::pi<float>() * r * R );
        float const x = cos(2*glm::pi<float>() * s * S) * sin( glm::pi<float>() * r * R );
        float const z = sin(2*glm::pi<float>() * s * S) * sin( glm::pi<float>() * r * R );

        (*v).position = glm::vec3(x * pRadius, y * pRadius, z * pRadius);
        (*v).normal = glm::vec3(x, y, z);
        (*v).color = glm::vec3(0.0f);
        (*v).texCoord = glm::vec2(s * S, r * R);

        v++;
    }

    mMesh->SetVertices(std::move(vertices));

    std::vector<unsigned int> indices(pRings * pSectors * 6);

    std::vector<unsigned int>::iterator i = indices.begin();
    for(r = 0; r < pRings-1; r++) for(s = 0; s < pSectors-1; s++)
    {
        *i++ = r * pSectors + (s+1);
        *i++ = r * pSectors + s;
        *i++ = (r+1) * pSectors + (s+1);

        *i++ = (r+1) * pSectors + (s+1);
        *i++ = r * pSectors + s;
        *i++ = (r+1) * pSectors + s;
    }

    mMesh->SetIndices(std::move(indices));

    mMesh->Setup();
}
