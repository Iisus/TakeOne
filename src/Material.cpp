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
    mTextures.back().Load();
}

void TakeOne::Material::SetTexture(const std::string& pUniformName, Texture&& pTexture)
{
    mTextures.push_back(std::move(pTexture));
    mTextures.back().Load(static_cast<unsigned int>(mProgram->GetUniformLocation(pUniformName)));
}

void TakeOne::Material::Use()
{
    assert(mProgram != nullptr && "The program from material must be set!");

    static std::shared_ptr<Program> sLastProgram = nullptr;
    if(sLastProgram != mProgram)
    {
        mProgram->Use();
        sLastProgram = mProgram;
    }

    for(const auto& texture:mTextures)
        texture.Bind();

    //TODO: Try switch instead of map
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
