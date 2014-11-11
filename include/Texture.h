#pragma once

#include <string>

namespace TakeOne
{
    class Texture
    {
    public:
        Texture();
        Texture(std::string pTexturePath);
        ~Texture();

        void Load(std::string pTexturePath);
        void Bind();
        void Unbind();
        void Unload();

    private:
        std::string mTexturePath;
        unsigned int mTextureId;

    };
}