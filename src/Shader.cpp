#include "Shader.h"
#include "FileLoader.h"
#include "Log.h"
#include "GL/glew.h"

TakeOne::Shader::Shader(const std::string &pShaderPath, ShaderType pShaderType)
        : mShaderPath(pShaderPath), mShaderType(pShaderType), mShaderId(0)
{
    Reload();
}

TakeOne::Shader::~Shader()
{
    Unload();
}

void TakeOne::Shader::Reload()
{
    Unload();
    Compile(TakeOne::FileLoader::LoadTextFile(mShaderPath));
}

unsigned int TakeOne::Shader::GetShaderId() const
{
    return mShaderId;
}

TakeOne::ShaderType TakeOne::Shader::GetShaderType() const
{
    return mShaderType;
}

void TakeOne::Shader::Compile(const std::string& pShaderSource)
{
    //Create Shder
    unsigned int type = GL_VERTEX_SHADER;
    if(mShaderType == ShaderType::FRAGMENT)
    {
        type = GL_FRAGMENT_SHADER;
    }
    mShaderId = glCreateShader(type);

    //Compile Shader
    const char* shaderSource = pShaderSource.c_str();
    glShaderSource(mShaderId, 1, &shaderSource, NULL);
    glCompileShader(mShaderId);

    // Check Shader
    int result = GL_FALSE;
    glGetShaderiv(mShaderId, GL_COMPILE_STATUS, &result);

    int infoLogLength;
    glGetShaderiv(mShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 1) //Usually returns 1 because the message is '\0'
    {
        std::string errorMessage;
        errorMessage.reserve(static_cast<unsigned long>(infoLogLength));
        glGetShaderInfoLog(mShaderId, infoLogLength, NULL, &errorMessage[0]);
        LOG_MSG("%s\n", errorMessage.c_str());
    }
    if(!result)
    {
        LOG_MSG("Shader did not compile!");
    }
}

void TakeOne::Shader::Unload()
{
    if(mShaderId)
    {
        glDeleteShader(mShaderId);
        mShaderId = 0;
    }
}
