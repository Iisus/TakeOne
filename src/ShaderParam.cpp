#include "ShaderParam.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GL/glew.h"

namespace TakeOne
{
    ShaderParamBase::~ShaderParamBase()
    {

    }

    //primary types
    template<>
    void ShaderParam<int>::SendToShader()
    {
        glUniform1iv(mId, mCount, &mValue);
    }

    template<>
    void ShaderParam<unsigned int>::SendToShader()
    {
        glUniform1uiv(mId, mCount, &mValue);
    }

    template<>
    void ShaderParam<float>::SendToShader()
    {
        glUniform1fv(mId, mCount, &mValue);
    }

    //vectors
    template<>
    void ShaderParam<glm::vec2>::SendToShader()
    {
        glUniform2fv(mId, mCount, glm::value_ptr(mValue));
    }

    template<>
    void ShaderParam<glm::vec3>::SendToShader()
    {
        glUniform3fv(mId, mCount, glm::value_ptr(mValue));
    }

    template<>
    void ShaderParam<glm::vec4>::SendToShader()
    {
        glUniform4fv(mId, mCount, glm::value_ptr(mValue));
    }

    //matrices
    template<>
    void ShaderParam<glm::mat2>::SendToShader()
    {
        glUniformMatrix2fv(mId, mCount, GL_FALSE, glm::value_ptr(mValue));
    }

    template<>
    void ShaderParam<glm::mat2x3>::SendToShader()
    {
        glUniformMatrix2x3fv(mId, mCount, GL_FALSE, glm::value_ptr(mValue));
    }

    template<>
    void ShaderParam<glm::mat2x4>::SendToShader()
    {
        glUniformMatrix2x4fv(mId, mCount, GL_FALSE, glm::value_ptr(mValue));
    }

    template<>
    void ShaderParam<glm::mat3>::SendToShader()
    {
        glUniformMatrix3fv(mId, mCount, GL_FALSE, glm::value_ptr(mValue));
    }

    template<>
    void ShaderParam<glm::mat3x2>::SendToShader()
    {
        glUniformMatrix3x2fv(mId, mCount, GL_FALSE, glm::value_ptr(mValue));
    }

    template<>
    void ShaderParam<glm::mat3x4>::SendToShader()
    {
        glUniformMatrix3x4fv(mId, mCount, GL_FALSE, glm::value_ptr(mValue));
    }

    template<>
    void ShaderParam<glm::mat4>::SendToShader()
    {
        glUniformMatrix4fv(mId, mCount, GL_FALSE, glm::value_ptr(mValue));
    }

    template<>
    void ShaderParam<glm::mat4x2>::SendToShader()
    {
        glUniformMatrix4x2fv(mId, mCount, GL_FALSE, glm::value_ptr(mValue));
    }

    template<>
    void ShaderParam<glm::mat4x3>::SendToShader()
    {
        glUniformMatrix4x3fv(mId, mCount, GL_FALSE, glm::value_ptr(mValue));
    }

}
