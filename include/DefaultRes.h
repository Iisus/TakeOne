#pragma once

#include "Program.h"
#include <string>

namespace TakeOne
{

    class DefaultRes
    {
    public:

        DefaultRes(std::string aResFolder);

        inline std::unique_ptr<Program> SimpleTextureProgram() const
        {
            return std::make_unique<Program>(mResFolder + "/default/shaders/SimpleTextureMap/vertex.glsl", mResFolder + "/default/shaders/SimpleTextureMap/fragment.glsl");
        }

    private:
        const std::string mResFolder;
    };
}
