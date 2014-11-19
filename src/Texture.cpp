#include <GL/glew.h>
#include "Texture.h"
#include "Log.h"
#include "SOIL.h"

TakeOne::Texture::Texture()
        : mTextureId(0)
{

}

TakeOne::Texture::Texture(std::string pTexturePath, unsigned int pTextureFlags)
        : mTextureId(0)
{
    Load(pTexturePath, pTextureFlags);
}

TakeOne::Texture::Texture(const unsigned char* const pBuffer, int pSize, unsigned int pTextureFlags)
        : mTextureId(0)
{
    Load(pBuffer, pSize, pTextureFlags);
}

TakeOne::Texture::~Texture()
{
    Unload();
}

void TakeOne::Texture::Load(std::string pTexturePath, unsigned int pTextureFlags)
{
    mTextureId = SOIL_load_OGL_texture
            (
                    pTexturePath.c_str(),
                    SOIL_LOAD_AUTO,
                    mTextureId ? mTextureId : SOIL_CREATE_NEW_ID, //if the texture was already loaded, overwrite it
                    pTextureFlags
            );
    if(!mTextureId)
    {
        LOG_MSG("Failed to load texture %s.", pTexturePath.c_str());
    }
}

void TakeOne::Texture::Load(const unsigned char* const pBuffer, int pSize, unsigned int pTextureFlags)
{
    mTextureId = SOIL_load_OGL_texture_from_memory
            (
                    pBuffer,
                    pSize,
                    SOIL_LOAD_AUTO,
                    mTextureId ? mTextureId : SOIL_CREATE_NEW_ID, //if the texture was already loaded, overwrite it
                    pTextureFlags
            );

    if(!mTextureId)
    {
        LOG_MSG("Failed to load texture from memory.");
    }
}

void TakeOne::Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, mTextureId);
}

void TakeOne::Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TakeOne::Texture::Unload()
{
    if (mTextureId!=0){
        Unbind();
        glDeleteTextures(1, &mTextureId);
        mTextureId = 0;
    }
}
