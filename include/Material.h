#pragma once

#include "ShaderParam.hpp"
#include "Program.h"
#include "GL/glew.h"
#include <string>
#include <vector>
#include <map>

namespace TakeOne
{
    typedef void (*glUniformFP)(int, int, ...);

    class Material
    {
    public:
        Material(std::unique_ptr<Program> pProgram);

        template<typename T>
        void SetParam(ShaderParamType pType, const std::string& pName, T pValue, int pCount = 1);
        void Use();
        void Reload();

    private:
        void InitGlUniformFPs();

        std::unique_ptr<Program> mProgram;
        std::vector<std::unique_ptr<ShaderParamBase>> mShaderParams;
        std::map<ShaderParamType, glUniformFP> mGlUniformFPs;
    };

    template<typename T>
    void Material::SetParam(ShaderParamType pType, const std::string& pName, T pValue, int pCount)
    {
        int id = mProgram->GetUniformLocation(pName);
        mShaderParams.push_back(std::unique_ptr<ShaderParamBase>(new ShaderParam<T>(id, pType, pName, pValue, pCount)));
    }
}