#include "Material.h"
#include <cassert>

template<typename T>
void TakeOne::Material::SetShaderParam(const std::string& pName, T pValue, int pCount)
{
    assert(mProgram != nullptr && "The program from material must be set!");

    if(mShaderParams.find(pName) != mShaderParams.end())
    {
        dynamic_cast<ShaderParam<T>*>(mShaderParams[pName].get())->SetValue(pValue);
    }
    else
    {
        mShaderParams[pName] = std::unique_ptr<ShaderParamBase>(
                new ShaderParam<T>(mProgram->GetUniformLocation(pName), pValue, pCount));
    }

    mShaderParams[pName]->SendToShader();
}

template<typename T>
void TakeOne::Material::SetShaderParam(DefaultPropertiesEnum pName, T pValue, int pCount)
{
    SetShaderParam<T>(kDefaultUniforms[pName], pValue, pCount);
}
