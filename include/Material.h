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
        struct DefaultProperties
        {
            glm::vec4 color_ambient;
            glm::vec4 color_diffuse;
            glm::vec4 color_emissive;
            glm::vec4 color_reflective;
            glm::vec4 color_specular;
            glm::vec4 color_transparent;

            float opacity;
            float reflectivity;
            float refractivity;
            float shininess;
            float shininess_strength;
        };

        enum DefaultPropertiesEnum
        {
            COLOR_AMBIENT,
            COLOR_DIFFUSE,
            COLOR_EMISSIVE,
            COLOR_REFLECTIVE,
            COLOR_SPECULAR,
            COLOR_TRANSPARENT,

            OPACITY,
            REFLECTIVITY,
            REFRACTIVITY,
            SHININESS,
            SHININESS_STRENGTH,

            Count
        };

    public:
        Material(std::shared_ptr<Program> pProgram = nullptr);

        template<typename T>
        void SetShaderParam(const std::string& pName, T pValue, int pCount = 1);
        template<typename T>
        void SetShaderParam(DefaultPropertiesEnum, T pValue, int pCount = 1);
        void ResendShaderParam(const std::string& pName);
        void ResendShaderParam(DefaultPropertiesEnum pName);
        void ResendShaderParams();
        void ApplyDefaultProperties(const std::vector<unsigned int>& pPropsUsed, const DefaultProperties& pDefaultProps);
        void SetTexture(Texture&& pTexture);
        void SetProgram(std::shared_ptr<Program> pProgram);
        void Use();
        void Reload();
        int GetTexturesCount();
    private:

        std::shared_ptr<Program> mProgram;
        std::vector<Texture> mTextures;
        std::unordered_map<std::string, std::unique_ptr<ShaderParamBase>> mShaderParams;

        static std::unordered_map<DefaultPropertiesEnum, std::string, std::hash<int>> kDefaultUniforms;
    };
}

#include "template_impl/Material.hpp"
