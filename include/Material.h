#pragma once

#include "ShaderParam.hpp"
#include "Program.h"
#include "Texture.h"
#include "GL/glew.h"
#include <string>
#include <vector>
#include <map>

namespace TakeOne
{
    class Material
    {
    public:
        Material();

        template<typename T>
        void SetShaderParam(const std::string& pName, T pValue, int pCount = 1);
        void SetProgram(std::unique_ptr<Program>&& pProgram);
        void SetTexture(std::unique_ptr<Texture>&& pTexture);
        void Use();
        void Reload();

    private:
        void InitGlUniformFPs();

        //alias for the lambda used in std::map
        using glUniformFP = void(*)(int, int, void*);

        std::unique_ptr<Program> mProgram;
        std::unique_ptr<Texture> mTexture;
        std::map<std::string, std::unique_ptr<ShaderParamBase>> mShaderParams;
        std::map<unsigned int, glUniformFP> mGlUniformFPs;
    };

    template<typename T>
    void Material::SetShaderParam(const std::string& pName, T pValue, int pCount)
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
    }
}