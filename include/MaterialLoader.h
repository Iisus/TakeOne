#pragma once

#include "Material.h"
#include "glm/glm.hpp"
#include <vector>
#include <string>

namespace TakeOne
{
    //TODO: Add an enum, size

    //helper class
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

    class MaterialLoader
    {
    public:
        void Apply(Material& pMaterial);
        void SetMaterialFormat(MaterialFormat&& pMaterialFormat);
        void SetFormatUsed(std::vector<unsigned int> pFormatsUsed);

        static const int NrOfUniforms = 11;
    private:
        MaterialFormat mMaterialFormat;
        std::vector<unsigned int> mFormatsUsed;
    };
}
