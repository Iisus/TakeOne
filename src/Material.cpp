#include "glm/glm.hpp"

#include "Material.h"

TakeOne::Material::Material(std::shared_ptr<Program> pProgram)
        : mProgram(pProgram)
{
}

void TakeOne::Material::SetProgram(std::shared_ptr<Program> pProgram)
{
    mProgram = pProgram;
}

void TakeOne::Material::SetTexture(Texture&& pTexture)
{
    mTextures.push_back(std::move(pTexture));
}

void TakeOne::Material::Use()
{
    assert(mProgram != nullptr && "The program from material must be set!");

    static unsigned int sLastProgramId = 0;
    if(!sLastProgramId || sLastProgramId != mProgram->GetLastProgramUsed())
    {
        mProgram->Use();
        sLastProgramId = mProgram->GetLastProgramUsed();
    }

    if(mTextures.empty())
        Texture::Unbind();

    int texNumber = 0;
    for(const auto& texture:mTextures)
    {
        glActiveTexture(GL_TEXTURE0 + texNumber);
        texture.Bind();
        texNumber++;
    }

    //send the uniforms to the shader
    for (auto& kv : mShaderParams)
    {
        kv.second->SendToShader();
    }
}

void TakeOne::Material::Reload()
{
    assert(mProgram != nullptr && "The program from material must be set!");

    mProgram->Reload();
}

int TakeOne::Material::GetTexturesCount()
{
    return mTextures.size();
}
