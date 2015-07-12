#pragma once

#include "ShaderParam.h"
#include "Program.h"
#include "Texture.h"
#include "GL/glew.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace TakeOne
{
    class Material
    {
    public:
        Material(std::shared_ptr<Program> pProgram = nullptr);

        template<typename T>
        void SetShaderParam(const std::string& pName, T pValue, int pCount = 1);
        void SetTexture(Texture&& pTexture);
        void SetTexture(const std::string& pUniformName, Texture&& pTexture);
        void SetProgram(std::shared_ptr<Program> pProgram);
        void Use();
        void Reload();
        int GetTexturesCount();
    private:

        std::shared_ptr<Program> mProgram;
        std::vector<Texture> mTextures;
        std::unordered_map<std::string, std::unique_ptr<ShaderParamBase>> mShaderParams;
    };
}

#include "template_impl/Material.hpp"
