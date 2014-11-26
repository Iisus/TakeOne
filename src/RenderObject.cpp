#include "RenderObject.h"
#include "MaterialHelper.h"
#include "Log.h"

TakeOne::RenderObject::RenderObject()
        : mMesh(new Mesh), mMaterial(new Material)
{

}

TakeOne::RenderObject::RenderObject(const std::string &pObjPath)
        : RenderObject()
{
    Load(pObjPath);
}

void TakeOne::RenderObject::Load(const std::string &pObjPath)
{
    //The components in file are floats
    std::ifstream file(pObjPath, std::ios::binary);
    if(!file.is_open())
    {
        LOG_MSG("Error loading file \"%s\"", pObjPath.c_str());
        file.close();
        return;
    }

    LoadMesh(file);
    LoadMaterial(file);

    file.close();
}

void TakeOne::RenderObject::Render()
{
    mMaterial->Use();
    mMesh->Render();
}

void TakeOne::RenderObject::LoadMesh(std::ifstream& pFile)
{
    //The header contains the vertex format (form: 11010, where 1 means that the component is used)
    // + vertex and index count
    unsigned long headerSize = static_cast<unsigned long>(VertexFormat::Count) + 2;

    std::vector<unsigned int> attribsUsed(headerSize);
    pFile.read(reinterpret_cast<char*>(&attribsUsed[0]), static_cast<long>(headerSize * sizeof(attribsUsed[0])));

    unsigned int indexCount  = (attribsUsed.back());
    attribsUsed.pop_back();
    unsigned int vertexCount = (attribsUsed.back());
    attribsUsed.pop_back();

    //Read vertices and indices
    std::vector<Vertex> vertices(vertexCount);
    pFile.read(reinterpret_cast<char*>(&vertices[0]), vertexCount * sizeof(vertices[0]));

    //Read in temporary buffer in order to convert from float to unsigned int
    std::vector<unsigned int> indices(indexCount);
    pFile.read(reinterpret_cast<char*>(&indices[0]), indexCount * sizeof(indices[0]));

    mMesh->SetAttribsUsed(attribsUsed);
    mMesh->SetVertices(vertices);
    mMesh->SetIndices(indices);

    mMesh->Setup();
}

void TakeOne::RenderObject::LoadMaterial(std::ifstream& pFile)
{
    MaterialHelper materialLoader;

    std::vector<unsigned int> formatUsed(MaterialHelper::FormatsNo);
    pFile.read(reinterpret_cast<char*>(&formatUsed[0]), MaterialHelper::FormatsNo * sizeof(formatUsed[0]));
    materialLoader.SetFormatUsed(std::move(formatUsed));

    MaterialHelper::MaterialFormat materialFormat;
    pFile.read(reinterpret_cast<char*>(&materialFormat), sizeof(materialFormat));
    materialLoader.SetMaterialFormat(std::move(materialFormat));

    materialLoader.Apply(*mMaterial);
}
