#include <glm/detail/type_vec.hpp>
#include "Material.h"

TakeOne::Material::Material(std::unique_ptr<Program> pProgram)
        : mProgram(std::move(pProgram))
{
    InitGlUniformFPs();
}

void TakeOne::Material::Use()
{
    mProgram->Use();

    //send the uniforms to the shader
    for(auto& shaderParam : mShaderParams)
    {
        ShaderParamType uniformType = shaderParam->GetType();
        auto glFunc = mGlUniformFPs[uniformType];

        //check if the uniform is a matrix or not; for matrices, the gl call has 4 arguments, for vectors it has 3
        if(static_cast<int>(uniformType) > static_cast<int>(ShaderParamType::UNIFORM_MATRIX))
        {
            glFunc(shaderParam->GetId(), shaderParam->GetCount(), GL_FALSE, shaderParam->GetValue());
        }
        else
        {
            glFunc(shaderParam->GetId(), shaderParam->GetCount(), shaderParam->GetValue());
        }
    }
}

void TakeOne::Material::Reload()
{
    mProgram->Reload();
}

void TakeOne::Material::InitGlUniformFPs()
{
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_1f, reinterpret_cast<glUniformFP>(glUniform1fv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_2f, reinterpret_cast<glUniformFP>(glUniform2fv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_3f, reinterpret_cast<glUniformFP>(glUniform3fv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_4f, reinterpret_cast<glUniformFP>(glUniform4fv)));

    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_1i, reinterpret_cast<glUniformFP>(glUniform1iv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_2i, reinterpret_cast<glUniformFP>(glUniform2iv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_3i, reinterpret_cast<glUniformFP>(glUniform3iv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_4i, reinterpret_cast<glUniformFP>(glUniform4iv)));

    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_1ui, reinterpret_cast<glUniformFP>(glUniform1uiv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_2ui, reinterpret_cast<glUniformFP>(glUniform2uiv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_3ui, reinterpret_cast<glUniformFP>(glUniform3uiv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_4ui, reinterpret_cast<glUniformFP>(glUniform4uiv)));

    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_2x2f, reinterpret_cast<glUniformFP>(glUniformMatrix2fv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_3x3f, reinterpret_cast<glUniformFP>(glUniformMatrix3fv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_4x4f, reinterpret_cast<glUniformFP>(glUniformMatrix4fv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_2x3f, reinterpret_cast<glUniformFP>(glUniformMatrix2x3fv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_3x2f, reinterpret_cast<glUniformFP>(glUniformMatrix3x2fv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_2x4f, reinterpret_cast<glUniformFP>(glUniformMatrix2x4fv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_4x2f, reinterpret_cast<glUniformFP>(glUniformMatrix4x2fv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_3x4f, reinterpret_cast<glUniformFP>(glUniformMatrix3x4fv)));
    mGlUniformFPs.insert(std::pair<ShaderParamType, glUniformFP>(ShaderParamType::UNIFORM_4x3f, reinterpret_cast<glUniformFP>(glUniformMatrix4x3fv)));
}
