#pragma once

#include "ShaderParam.hpp"
#include "Program.h"
#include "GL/glew.h"
#include <string>
#include <vector>
#include <map>

namespace TakeOne
{
    class Material
    {
    public:
        Material(std::unique_ptr<Program>&& pProgram);

        template<typename T>
        void SetParam(const std::string& pName, T pValue, int pCount = 1);
        void Use();
        void Reload();

    private:
        void InitGlUniformFPs();

        //alias for the lambda used in std::map
        using glUniformFP = void(*)(int, int, void*);

        std::unique_ptr<Program> mProgram;
        std::map<std::string, std::unique_ptr<ShaderParamBase>> mShaderParams;
        std::map<unsigned int, glUniformFP> mGlUniformFPs;
    };

    template<typename T>
    void Material::SetParam(const std::string& pName, T pValue, int pCount)
    {
        if(mShaderParams.find(pName) != mShaderParams.end())
        {
            dynamic_cast<ShaderParam<T>*>(mShaderParams[pName].get())->SetValue(pValue);
        }
        else
        {
            mShaderParams[pName] = std::unique_ptr<ShaderParamBase>(
                    new ShaderParam<T>(mProgram->GetUniformLocation(pName), pValue, pCount));
        }
    }
}