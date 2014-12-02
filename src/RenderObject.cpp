#include "RenderObject.h"
#include "MaterialHelper.h"
#include "Log.h"
#include <sstream>

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

    //The header contains the uniforms used(form: 11010, where 1 means that the uniform is used)
    // + textures string size
    unsigned long headerSize = MaterialHelper::Count + 1;

    std::vector<unsigned int> formatUsed(headerSize);
    pFile.read(reinterpret_cast<char*>(&formatUsed[0]), headerSize * sizeof(formatUsed[0]));
    unsigned int texStringSize = formatUsed.back();
    formatUsed.pop_back();
    materialLoader.SetFormatUsed(std::move(formatUsed));

    MaterialHelper::MaterialFormat materialFormat;
    pFile.read(reinterpret_cast<char*>(&materialFormat), sizeof(materialFormat));
    materialLoader.SetMaterialFormat(std::move(materialFormat));

    char* texPaths = new char[texStringSize];
    pFile.read(texPaths, texStringSize);

    std::stringstream ss((std::string(texPaths)));
    std::string item;
    while (std::getline(ss, item, ' '))
    {
        item = "../res/textures/" + item;
        Texture texture(item, Texture::INVERT_Y);
        mMaterial->SetTexture(std::move(texture));
    }

    materialLoader.Apply(*mMaterial);
}
