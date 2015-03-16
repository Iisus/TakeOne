#include <GL/glew.h>
#include "Texture.h"
#include "Log.h"
#include "SOIL.h"

TakeOne::Texture::Texture(std::string pTexturePath, unsigned int pTextureFlags) :
    mTexturePath(pTexturePath), mTextureFlags(pTextureFlags), mTextureId(0)
{

}


TakeOne::Texture::Texture(TakeOne::Texture &&pTexture) :
    mTexturePath(std::move(pTexture.mTexturePath)), mTextureFlags(std::move(pTexture.mTextureFlags)),
    mTextureId(std::move(pTexture.mTextureId))
{
    pTexture.mTexturePath = "";
    pTexture.mTextureFlags = 0;
    pTexture.mTextureId = 0;
}

TakeOne::Texture& TakeOne::Texture::operator=(TakeOne::Texture &&pTexture)
{
    if(this != &pTexture)
    {
        Unload();
        mTexturePath = std::move(pTexture.mTexturePath);
        mTextureFlags = std::move(pTexture.mTextureFlags);
        mTextureId = std::move(pTexture.mTextureId);

        pTexture.mTexturePath = "";
        pTexture.mTextureFlags = 0;
        pTexture.mTextureId = 0;
    }
    return *this;
}

TakeOne::Texture::~Texture()
{
    Unload();
}

void TakeOne::Texture::Load(unsigned int pTextureId)
{
    mTextureId = pTextureId;

    mTextureId = SOIL_load_OGL_texture
            (
                mTexturePath.c_str(),
                SOIL_LOAD_AUTO,
                mTextureId ? mTextureId : SOIL_CREATE_NEW_ID,
                mTextureFlags
            );
    if(!mTextureId)
    {
        LOG_MSG("Failed to load texture \"%s\".", mTexturePath.c_str());
    }
}

void TakeOne::Texture::LoadFromFile(std::string pTexturePath, unsigned int pTextureFlags, unsigned int pTextureId)
{
    mTexturePath = pTexturePath;
    mTextureFlags = pTextureFlags;

    Load(pTextureId);
}

void TakeOne::Texture::LoadFromBuffer(const unsigned char* const pBuffer, int pSize, unsigned int pTextureFlags,  unsigned int pTextureId)
{
    mTextureFlags = pTextureFlags;
    mTextureId = pTextureId;

    mTextureId = SOIL_load_OGL_texture_from_memory
            (
                pBuffer,
                pSize,
                SOIL_LOAD_AUTO,
                mTextureId ? mTextureId : SOIL_CREATE_NEW_ID, //if the texture was already loaded, overwrite it
                mTextureFlags
            );

    if(!mTextureId)
    {
        LOG_MSG("Failed to load texture from memory.");
    }
}

void TakeOne::Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, mTextureId);
}

void TakeOne::Texture::Unbind() const
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
