#include "RenderObject.h"
#include "MaterialHelper.h"
#include "Log.h"
#include <sstream>

TakeOne::RenderObject::RenderObject(std::shared_ptr<Program> pProgram)
        : mMesh(new Mesh), mMaterial(new Material(pProgram)), mRenderable(true)
{

}

TakeOne::RenderObject::RenderObject(std::shared_ptr<Program> pProgram, const std::string &pObjPath, const std::string &pObjName)
        : mMesh(new Mesh), mMaterial(new Material(pProgram)), mRenderable(true)
{
    Load(pObjPath, pObjName);
}

void TakeOne::RenderObject::SetProgram(std::shared_ptr<Program> pProgram)
{
    mMaterial->SetProgram(pProgram);
}

void TakeOne::RenderObject::Load(const std::string &pObjPath, const std::string &pObjName)
{
    if(!pObjPath.empty())
    {
        mObjPath = pObjPath;
        mObjName = mObjName;
        //The components in file are floats
        std::ifstream file(mObjPath + pObjName + ".t1o", std::ios::binary);
        if (!file.is_open())
        {
            LOG_MSG("Error loading file \"%s\"", mObjPath.c_str());
            file.close();
            return;
        }

        LoadMesh(file);
        LoadMaterial(file);

        file.close();
    }
}

void TakeOne::RenderObject::Render() const
{
    if(mRenderable)
    {
        mMaterial->Use();
        mMesh->Render();
    }
}

void TakeOne::RenderObject::LoadMesh(std::ifstream& pFile)
{
    //The header contains the vertex format (form: 11010, where 1 means that the component is used)
    // + vertex and index count
    unsigned long headerSize = Vertex::Count + 2;

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

    mMesh->SetAttribsUsed(std::move(attribsUsed));
    mMesh->SetVertices(std::move(vertices));
    mMesh->SetIndices(std::move(indices));

    mMesh->Setup();
}

void TakeOne::RenderObject::LoadMaterial(std::ifstream& pFile)
{
    MaterialHelper materialLoader;

    //The header contains the uniforms used(form: 11010, where 1 means that the uniform is used)
    // + textures string size
    unsigned long headerSize = MaterialHelper::Count + 1;

    std::vector<unsigned int> formatUsed(headerSize);
    pFile.read(reinterpret_cast<char*>(&formatUsed[0]), static_cast<long>(headerSize * sizeof(formatUsed[0])));
    unsigned int texStringSize = formatUsed.back();
    formatUsed.pop_back();
    materialLoader.SetFormatUsed(std::move(formatUsed));

    MaterialHelper::MaterialFormat materialFormat;
    pFile.read(reinterpret_cast<char*>(&materialFormat), sizeof(materialFormat));
    materialLoader.SetMaterialFormat(std::move(materialFormat));


    char* texPaths = new char[texStringSize+1];
    pFile.read(texPaths, texStringSize);
    texPaths[texStringSize] = 0;

    std::stringstream ss((std::string(texPaths)));
    delete[] texPaths;

    std::string item;

    while (std::getline(ss, item, '&'))
    {
        mMaterial->SetTexture(Texture(mObjPath + item, Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS));
    }

    materialLoader.Apply(*mMaterial);
}
