#include <GL/glew.h>
#include "Texture.h"
#include "Log.h"
#include "SOIL.h"

TakeOne::Texture::Texture()
        : mTextureId(0)
{

}

TakeOne::Texture::Texture(std::string pTexturePath)
        : mTextureId(0)
{
    Load(pTexturePath);
}

TakeOne::Texture::~Texture()
{
    Unload();
}

void TakeOne::Texture::Load(std::string pTexturePath)
{
    mTexturePath = pTexturePath;

    mTextureId = SOIL_load_OGL_texture
            (
                    pTexturePath.c_str(),
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    if(!mTextureId)
    {
        LOG_MSG("Failed to load texture %s", pTexturePath.c_str());
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
