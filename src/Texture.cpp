#include <GL/glew.h>
#include "Texture.h"
#include "Log.h"
#include "SOIL.h"

std::unordered_map<std::string, std::pair<int, int>> TakeOne::Texture::mUsedTextures;

TakeOne::Texture::Texture()
{

}

TakeOne::Texture::Texture(std::string pTexturePath, unsigned int pTextureFlags, unsigned int pTextureNo)
{
    LoadFromFile(pTexturePath, pTextureFlags, pTextureNo);
}


TakeOne::Texture::Texture(TakeOne::Texture &&pTexture) :
    mTexturePath(std::move(pTexture.mTexturePath)), mTextureFlags(std::move(pTexture.mTextureFlags)),
    mTextureNo(std::move(pTexture.mTextureNo)), mTextureId(std::move(pTexture.mTextureId))
{
    pTexture.mTexturePath = "";
    pTexture.mTextureFlags = 0;
    pTexture.mTextureNo = 0;
    pTexture.mTextureId = 0;
}

TakeOne::Texture& TakeOne::Texture::operator=(TakeOne::Texture &&pTexture)
{
    if(this != &pTexture)
    {
        Unload();
        mTexturePath = std::move(pTexture.mTexturePath);
        mTextureFlags = std::move(pTexture.mTextureFlags);
        mTextureNo = std::move(pTexture.mTextureNo);
        mTextureId = std::move(pTexture.mTextureId);

        pTexture.mTexturePath = "";
        pTexture.mTextureFlags = 0;
        pTexture.mTextureNo = 0;
        pTexture.mTextureId = 0;
    }
    return *this;
}

TakeOne::Texture::~Texture()
{
    Unload();
}

void TakeOne::Texture::LoadFromFile(std::string pTexturePath, unsigned int pTextureFlags, unsigned int pTextureNo, unsigned int pTextureId)
{
    mTexturePath = pTexturePath;
    mTextureFlags = pTextureFlags;
    mTextureNo = pTextureNo;

    Load(pTextureId);
}

void TakeOne::Texture::LoadFromBuffer(const unsigned char* const pBuffer, int pSize, unsigned int pTextureFlags, unsigned int pTextureNo, unsigned int pTextureId)
{
    Unload();

    mTextureFlags = pTextureFlags;
    mTextureId = pTextureId;
    mTextureNo = pTextureNo;

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
    glActiveTexture(GL_TEXTURE0 + mTextureNo);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
}

void TakeOne::Texture::Unload()
{
    if (mTextureId!=0){
        Unbind();

        if(mUsedTextures.find(mTexturePath) != mUsedTextures.end() && mUsedTextures[mTexturePath].second > 1)
        {
            mUsedTextures[mTexturePath].second--;
        }
        else
        {
            glDeleteTextures(1, &mTextureId);
            mUsedTextures.erase(mTexturePath);
        }

        mTextureId = 0;
    }
}

void TakeOne::Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TakeOne::Texture::Load(unsigned int pTextureId)
{
    //if the user doesn't want a specific texture id and the texture was already loaded
    if(pTextureId == 0 && mUsedTextures.find(mTexturePath) != mUsedTextures.end())
    {
        mTextureId = mUsedTextures[mTexturePath].first;
        mUsedTextures[mTexturePath].second++; //ref count
    }
    else
    {
        Unload();

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

        mUsedTextures[mTexturePath] = std::make_pair(mTextureId, 1);
    }
}
