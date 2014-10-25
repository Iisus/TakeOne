#include "GL/glew.h"
#include "Log.h"
#include "Mesh.h"

TakeOne::Mesh::Mesh()
: mVAO(0), mVBO(0), mIBO(0)
{
}

TakeOne::Mesh::~Mesh()
{
    Release();
}

void TakeOne::Mesh::Setup(const std::vector<Vertex>& pVertices, const std::vector<unsigned int>& pIndices, const std::bitset<5>& pAttribsUsed)
{
    assert(pAttribsUsed[(unsigned int)VertexFormat::POSITION] && "A mesh must contain positions!");

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, pVertices.size() * sizeof(Vertex), &pVertices[0], GL_STATIC_DRAW);


    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);

    //find out the minimum size for indices
    if(pVertices.size() < 0xff)
    {
        mIndicesType = GL_UNSIGNED_BYTE;
        std::vector<unsigned char> charIndices(pIndices.begin(), pIndices.end());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, charIndices.size() * sizeof(unsigned char), &charIndices[0], GL_STATIC_DRAW);
    }
    else if(pVertices.size() < 0xffff)
    {
        mIndicesType = GL_UNSIGNED_SHORT;
        std::vector<unsigned short> shortIndices(pIndices.begin(), pIndices.end());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, shortIndices.size() * sizeof(unsigned short), &shortIndices[0], GL_STATIC_DRAW);
    }
    else
    {
        mIndicesType = GL_UNSIGNED_INT;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, pIndices.size() * sizeof(unsigned int), &pIndices[0], GL_STATIC_DRAW);
    }

    mVertices       = pVertices;
    mIndices        = pIndices;
    mAttribsUsed    = pAttribsUsed;
}

void TakeOne::Mesh::Render()
{
    glBindVertexArray(mVAO);

    //Bind vertex data
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    unsigned int attribLocation;
    if(mAttribsUsed[(unsigned int)VertexFormat::POSITION])
    {
        attribLocation = (unsigned int)VertexFormat::POSITION;
        glEnableVertexAttribArray(attribLocation);
        glVertexAttribPointer(
                attribLocation,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                (void*) offsetof(Vertex, position)
        );
    }

    if(mAttribsUsed[(unsigned int)VertexFormat::NORMAL])
    {
        attribLocation = (unsigned int)VertexFormat::NORMAL;
        glEnableVertexAttribArray(attribLocation);
        glVertexAttribPointer(
                attribLocation,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                (void*) offsetof(Vertex, normal)
        );
    }

    if(mAttribsUsed[(unsigned int)VertexFormat::COLOR])
    {
        attribLocation = (unsigned int)VertexFormat::COLOR;
        glEnableVertexAttribArray(attribLocation);
        glVertexAttribPointer(
                attribLocation,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                (void*) offsetof(Vertex, color)
        );
    }

    if(mAttribsUsed[(unsigned int)VertexFormat::TANGENT])
    {
        attribLocation = (unsigned int)VertexFormat::TANGENT;
        glEnableVertexAttribArray(attribLocation);
        glVertexAttribPointer(
                attribLocation,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                (void*) offsetof(Vertex, tangent)
        );
    }

    if(mAttribsUsed[(unsigned int)VertexFormat::TEXTCOORD])
    {
        attribLocation = (unsigned int)VertexFormat::TEXTCOORD;
        glEnableVertexAttribArray(attribLocation);
        glVertexAttribPointer(
                attribLocation,
                2,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                (void*) offsetof(Vertex, textCoord)
        );
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glDrawElements(
            GL_TRIANGLES,
            mIndices.size(),
            mIndicesType,
            (void*)0
    );
}

void TakeOne::Mesh::Release()
{
    if(mVAO)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glDeleteVertexArrays(1, &mVAO);
        glDeleteBuffers(1, &mVBO);
        glDeleteBuffers(1, &mIBO);
    }
}