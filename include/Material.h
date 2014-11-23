#pragma once

#include "ShaderParam.h"
#include "Program.h"
#include "Texture.h"
#include "GL/glew.h"
#include <string>
#include <vector>
#include <typeindex>
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
        std::map<std::type_index, glUniformFP> mGlUniformFPs;
    };
}

#include "template_impl/Material.hpp"
