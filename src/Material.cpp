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

    static unsigned int sLastProgramId = mProgram->GetLoadCounter() + 1;
    if(sLastProgramId != mProgram->GetLoadCounter())
    {
        mProgram->Use();
        sLastProgramId = mProgram->GetLoadCounter();
    }

    for(const auto& texture:mTextures)
        texture.Bind();

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
