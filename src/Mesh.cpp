#include "GL/glew.h"
#include "Log.h"
#include "Mesh.h"
#include <fstream>

TakeOne::Mesh::Mesh() :
    mVAO(0), mVBO(0), mIBO(0)
{

}

TakeOne::Mesh::Mesh(Mesh&& pOther) :
    mVAO(std::move(pOther.mVAO)), mVBO(std::move(pOther.mVBO)), mIBO(std::move(pOther.mIBO)),
    mIndicesType(std::move(pOther.mIndicesType)), mIndices(std::move(pOther.mIndices)),
    mVertices(std::move(pOther.mVertices)), mAttribsUsed(std::move(pOther.mAttribsUsed))
{
    //Reset only the mVAO for the other object, so that the buffers are not destroyed (see ~Mesh())
    pOther.mVAO = 0;
}

TakeOne::Mesh& TakeOne::Mesh::operator=(Mesh&& pOther)
{
    if(this != &pOther)
    {
        Release();

        mVAO = std::move(pOther.mVAO);
        mVBO = std::move(pOther.mVBO);
        mIBO = std::move(pOther.mIBO);
        mIndicesType = std::move(pOther.mIndicesType);
        mIndices = std::move(pOther.mIndices);
        mVertices = std::move(pOther.mVertices);
        mAttribsUsed = std::move(pOther.mAttribsUsed);

        //Reset only the mVAO for the other object, so that the buffers are not destroyed (see ~Mesh())
        pOther.mVAO = 0;
    }
    return *this;
}

TakeOne::Mesh::~Mesh()
{
    Release();
}

void TakeOne::Mesh::Render()
{
    glBindVertexArray(mVAO);

    //Bind vertex data
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    if(mAttribsUsed[Vertex::POSITION])
    {
        glEnableVertexAttribArray(Vertex::POSITION);
        glVertexAttribPointer(
                Vertex::POSITION,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                reinterpret_cast<const void*>(offsetof(Vertex, position))
        );
    }

    if(mAttribsUsed[Vertex::NORMAL])
    {
        glEnableVertexAttribArray(Vertex::NORMAL);
        glVertexAttribPointer(
                Vertex::NORMAL,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                reinterpret_cast<const void*>(offsetof(Vertex, normal))
        );
    }

    if(mAttribsUsed[Vertex::COLOR])
    {
        glEnableVertexAttribArray(Vertex::COLOR);
        glVertexAttribPointer(
                Vertex::COLOR,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                reinterpret_cast<const void*>(offsetof(Vertex, color))
        );
    }

    if(mAttribsUsed[Vertex::TEXCOORD])
    {
        glEnableVertexAttribArray(Vertex::TEXCOORD);
        glVertexAttribPointer(
                Vertex::TEXCOORD,
                2,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                reinterpret_cast<const void*>(offsetof(Vertex, texCoord))
        );
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glDrawElements(
            GL_TRIANGLES,
            static_cast<int>(mIndices.size()),
            mIndicesType,
            reinterpret_cast<const void*>(0)
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

void TakeOne::Mesh::Setup()
{
    Release();

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);


    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);

    //find out the minimum size for indices
    if(mVertices.size() < sizeof(unsigned char))
    {
        mIndicesType = GL_UNSIGNED_BYTE;
        std::vector<unsigned char> charIndices(mIndices.begin(), mIndices.end());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, charIndices.size() * sizeof(unsigned char), &charIndices[0], GL_STATIC_DRAW);
    }
    else if(mVertices.size() < sizeof(unsigned short))
    {
        mIndicesType = GL_UNSIGNED_SHORT;
        std::vector<unsigned short> shortIndices(mIndices.begin(), mIndices.end());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, shortIndices.size() * sizeof(unsigned short), &shortIndices[0], GL_STATIC_DRAW);
    }
    else
    {
        mIndicesType = GL_UNSIGNED_INT;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);
    }
}
