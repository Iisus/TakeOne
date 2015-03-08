#pragma once
#include <string>

namespace TakeOne
{
    enum class ShaderType
    {
        VERTEX,
        FRAGMENT
    };

    class Shader
    {
    public:
        Shader(const std::string &pShaderPath, ShaderType pShaderType);
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        Shader(Shader&&);
        Shader& operator=(Shader&&);
        ~Shader();

        void Reload();

        unsigned int GetShaderId() const;
        ShaderType GetShaderType() const;

    private:
        void Compile(const std::string& pShaderSource);
        void Unload();

        std::string mShaderPath;
        ShaderType mShaderType;
        unsigned int mShaderId;
    };
}
