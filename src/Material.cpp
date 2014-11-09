#include "Material.h"

TakeOne::Material::Material(std::unique_ptr<Program> pProgram)
        : mProgram(std::move(pProgram))
{

}

void TakeOne::Material::SetParam(ShaderParamType pType, const std::string& pName, const float* pValue, int pCount)
{
    int id = mProgram->GetUniformLocation(pName);
    mShaderParams.push_back(ShaderParam(id, pType, pName, pValue, pCount));
}
