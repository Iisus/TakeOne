#pragma once

#include "Program.h"
#include <string>

namespace TakeOne
{

    class DefaultRes
    {
    public:

        DefaultRes(std::string pResFolder);

        inline std::unique_ptr<Program> SimpleTextureMapProgram() const
        {
            return std::make_unique<Program>(mResFolder + "/default/shaders/SimpleTextureMap/vertex.glsl", mResFolder + "/default/shaders/SimpleTextureMap/fragment.glsl");
        }

        inline std::unique_ptr<Program> UberShaderProgram() const
        {
            return std::make_unique<Program>(mResFolder + "/default/shaders/UberShader/vertex.glsl", mResFolder + "/default/shaders/UberShader/fragment.glsl");
        }

        inline std::unique_ptr<Program> SimpleTextureProgram() const
        {
            return std::make_unique<Program>(mResFolder + "/default/shaders/SimpleTexture/vertex.glsl", mResFolder + "/default/shaders/SimpleTexture/fragment.glsl");
        }

        inline std::unique_ptr<Program> SpecularMapProgram() const
        {
            return std::make_unique<Program>(mResFolder + "/default/shaders/SpecularMap/vertex.glsl", mResFolder + "/default/shaders/SpecularMap/fragment.glsl");
        }

    private:
        const std::string mResFolder;
    };
}
