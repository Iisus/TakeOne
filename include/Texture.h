#pragma once

#include <string>
#include <unordered_map>

namespace TakeOne
{
    class Texture
    {
    public:
        Texture();
        Texture(const std::string pTexturePath, unsigned int pTextureFlags);

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        Texture(Texture&&);
        Texture& operator=(Texture&&);

        ~Texture();

        void LoadFromFile(const std::string pTexturePath, unsigned int pTextureFlags, unsigned int pTextureId = 0);
        void LoadFromBuffer(const unsigned char* const pBuffer, int pSize, unsigned int pTextureFlags, unsigned int pTextureId = 0);
        void Bind() const;
        void Unbind() const;
        void Unload();

        //match SOIL flags, so SOIL is not exposed
        enum Flag : unsigned int
        {
            NONE = 0,
            POWER_OF_TWO = 1,       //force the image to be POT
            MIPMAPS = 2,            //generate mipmaps for the texture
            TEXTURE_REPEATS = 4,    //otherwise will clamp
            MULTIPLY_ALPHA = 8,     //for using (GL_ONE,GL_ONE_MINUS_SRC_ALPHA) blending
            INVERT_Y = 16,          //flip the image vertically
            COMPRESS_TO_DXT = 32,   //if the card can display them, will convert RGB to DXT1, RGBA to DXT5
            DDS_LOAD_DIRECT = 64,   //will load DDS files directly without _ANY_ additional processing
            NTSC_SAFE_RGB = 128,    //clamps RGB components to the range [16,235]
            CoCg_Y = 256,           //Google YCoCg; RGB=>CoYCg, RGBA=>CoCgAY
            TEXTURE_RECTANGLE = 512 //uses ARB_texture_rectangle ; pixel indexed & no repeat or MIPmaps or cubemaps
        };

    private:
        void Load(unsigned int pTextureId = 0);

        std::string mTexturePath;
        unsigned int mTextureFlags;
        unsigned int mTextureId;

        //unordered_map< TexturPath, pair< TextureId, RefCount> >
        static std::unordered_map<std::string, std::pair<int, int>> mUsedTextures;
    };
}
