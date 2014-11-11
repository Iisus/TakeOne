#include <glm/detail/type_vec.hpp>
#include "Material.h"

TakeOne::Material::Material(std::unique_ptr<Program>&& pProgram)
        : mProgram(std::move(pProgram))
{
    InitGlUniformFPs();
}

void TakeOne::Material::Use()
{
    mProgram->Use();

    //send the uniforms to the shader
    for (auto it=mShaderParams.begin(); it!=mShaderParams.end(); ++it)
    {
        //call glUniform* function from the map
        mGlUniformFPs[it->second->GetTypeHash()](it->second->GetId(), it->second->GetCount(), it->second->GetValue());
    }
}

void TakeOne::Material::Reload()
{
    mProgram->Reload();
}

void TakeOne::Material::InitGlUniformFPs()
{
    //primitives
    mGlUniformFPs[typeid(float).hash_code()] = [](int id, int count, void* value){
        glUniform1fv(id, count, (float*)value);
    };
    mGlUniformFPs[typeid(int).hash_code()] = [](int id, int count, void* value){
        glUniform1iv(id, count, (int*)value);
    };
    mGlUniformFPs[typeid(unsigned int).hash_code()] = [](int id, int count, void* value){
        glUniform1uiv(id, count, (unsigned int*)value);
    };

    //vectors
    mGlUniformFPs[typeid(glm::vec2).hash_code()] = [](int id, int count, void* value){
        glUniform2fv(id, count, (float*)value);
    };
    mGlUniformFPs[typeid(glm::vec3).hash_code()] = [](int id, int count, void* value){
        glUniform3fv(id, count, (float*)value);
    };
    mGlUniformFPs[typeid(glm::vec4).hash_code()] = [](int id, int count, void* value){
        glUniform4fv(id, count, (float*)value);
    };

    //matrices
    mGlUniformFPs[typeid(glm::mat2).hash_code()] = [](int id, int count, void* value){
        glUniformMatrix2fv(id, count, GL_FALSE, (float*)value);
    };
    mGlUniformFPs[typeid(glm::mat2x3).hash_code()] = [](int id, int count, void* value){
        glUniformMatrix2x3fv(id, count, GL_FALSE, (float*)value);
    };
    mGlUniformFPs[typeid(glm::mat2x4).hash_code()] = [](int id, int count, void* value){
        glUniformMatrix2x4fv(id, count, GL_FALSE, (float*)value);
    };

    mGlUniformFPs[typeid(glm::mat3).hash_code()] = [](int id, int count, void* value){
        glUniformMatrix3fv(id, count, GL_FALSE, (float*)value);
    };
    mGlUniformFPs[typeid(glm::mat3x2).hash_code()] = [](int id, int count, void* value){
        glUniformMatrix3x2fv(id, count, GL_FALSE, (float*)value);
    };
    mGlUniformFPs[typeid(glm::mat3x4).hash_code()] = [](int id, int count, void* value){
        glUniformMatrix3x4fv(id, count, GL_FALSE, (float*)value);
    };

    mGlUniformFPs[typeid(glm::mat4).hash_code()] = [](int id, int count, void* value){
        glUniformMatrix4fv(id, count, GL_FALSE, (float*)value);
    };
    mGlUniformFPs[typeid(glm::mat4x2).hash_code()] = [](int id, int count, void* value){
        glUniformMatrix4x2fv(id, count, GL_FALSE, (float*)value);
    };
    mGlUniformFPs[typeid(glm::mat4x3).hash_code()] = [](int id, int count, void* value){
        glUniformMatrix4x3fv(id, count, GL_FALSE, (float*)value);
    };
}
