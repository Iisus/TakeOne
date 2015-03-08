#pragma once

#include "Material.h"
#include "glm/glm.hpp"
#include <vector>
#include <string>

namespace TakeOne
{
    class MaterialHelper
    {
    public:
        struct MaterialFormat
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

        enum MaterialFormatEnum
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

        void Apply(Material& pMaterial);
        void SetMaterialFormat(MaterialFormat&& pMaterialFormat);
        void SetFormatUsed(std::vector<unsigned int>&& pFormatsUsed);

    private:
        MaterialFormat mMaterialFormat;
        std::vector<unsigned int> mFormatsUsed;
    };
}
