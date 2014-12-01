#include "glm/glm.hpp"

#include "Material.h"

TakeOne::Material::Material()
        : mProgram(nullptr)
{
    InitGlUniformFPs();
}

void TakeOne::Material::SetProgram(std::unique_ptr<Program>&& pProgram)
{
    mProgram = std::move(pProgram);
}

void TakeOne::Material::SetTexture(const std::string& pUniformName, std::unique_ptr<Texture> pTexture)
{
    mTextures.push_back(std::move(pTexture));
    mTextures.back()->Load(static_cast<unsigned int>(mProgram->GetUniformLocation(pUniformName)));
}

void TakeOne::Material::Use()
{
    assert(mProgram != nullptr && "The program from material must be set!");

    mProgram->Use();

    for(const auto& texture:mTextures)
        texture->Bind();

    //send the uniforms to the shader
    for (auto it=mShaderParams.begin(); it!=mShaderParams.end(); ++it)
    {
        //call glUniform* function from the map
        mGlUniformFPs[it->second->GetTypeIndex()]
                (
                        it->second->GetId(),
                        it->second->GetCount(),
                        it->second->GetValue()
                );
    }
}

void TakeOne::Material::Reload()
{
    assert(mProgram != nullptr && "The program from material must be set!");

    mProgram->Reload();
}

void TakeOne::Material::InitGlUniformFPs()
{
    //primitives
    mGlUniformFPs[typeid(float)] = [](int id, int count, void* value){
        glUniform1fv(id, count, static_cast<float*>(value));
    };
    mGlUniformFPs[typeid(int)] = [](int id, int count, void* value){
        glUniform1iv(id, count, static_cast<int*>(value));
    };
    mGlUniformFPs[typeid(unsigned int)] = [](int id, int count, void* value){
        glUniform1uiv(id, count, static_cast<unsigned int*>(value));
    };

    //vectors
    mGlUniformFPs[typeid(glm::vec2)] = [](int id, int count, void* value){
        glUniform2fv(id, count, static_cast<float*>(value));
    };
    mGlUniformFPs[typeid(glm::vec3)] = [](int id, int count, void* value){
        glUniform3fv(id, count, static_cast<float*>(value));
    };
    mGlUniformFPs[typeid(glm::vec4)] = [](int id, int count, void* value){
        glUniform4fv(id, count, static_cast<float*>(value));
    };

    //matrices
    mGlUniformFPs[typeid(glm::mat2)] = [](int id, int count, void* value){
        glUniformMatrix2fv(id, count, GL_FALSE, static_cast<float*>(value));
    };
    mGlUniformFPs[typeid(glm::mat2x3)] = [](int id, int count, void* value){
        glUniformMatrix2x3fv(id, count, GL_FALSE, static_cast<float*>(value));
    };
    mGlUniformFPs[typeid(glm::mat2x4)] = [](int id, int count, void* value){
        glUniformMatrix2x4fv(id, count, GL_FALSE, static_cast<float*>(value));
    };

    mGlUniformFPs[typeid(glm::mat3)] = [](int id, int count, void* value){
        glUniformMatrix3fv(id, count, GL_FALSE, static_cast<float*>(value));
    };
    mGlUniformFPs[typeid(glm::mat3x2)] = [](int id, int count, void* value){
        glUniformMatrix3x2fv(id, count, GL_FALSE, static_cast<float*>(value));
    };
    mGlUniformFPs[typeid(glm::mat3x4)] = [](int id, int count, void* value){
        glUniformMatrix3x4fv(id, count, GL_FALSE, static_cast<float*>(value));
    };

    mGlUniformFPs[typeid(glm::mat4)] = [](int id, int count, void* value){
        glUniformMatrix4fv(id, count, GL_FALSE, static_cast<float*>(value));
    };
    mGlUniformFPs[typeid(glm::mat4x2)] = [](int id, int count, void* value){
        glUniformMatrix4x2fv(id, count, GL_FALSE, static_cast<float*>(value));
    };
    mGlUniformFPs[typeid(glm::mat4x3)] = [](int id, int count, void* value){
        glUniformMatrix4x3fv(id, count, GL_FALSE, static_cast<float*>(value));
    };
}
