#include "glm/glm.hpp"

#include "Material.h"

std::unordered_map<TakeOne::Material::DefaultPropertiesEnum, std::string, std::hash<int>> TakeOne::Material::kDefaultUniforms =
{
    {COLOR_AMBIENT, "u_ColorAmbient"},
    {COLOR_DIFFUSE, "u_ColorDiffuse"},
    {COLOR_EMISSIVE, "u_ColorEmissive"},
    {COLOR_REFLECTIVE, "u_ColorReflective"},
    {COLOR_SPECULAR, "u_ColorSpecular"},
    {COLOR_TRANSPARENT, "u_ColorTransparent"},

    {OPACITY, "u_Opacity"},
    {REFLECTIVITY, "u_Reflectivity"},
    {REFRACTIVITY, "u_Refractivity"},
    {SHININESS, "u_Shininess"},
    {SHININESS_STRENGTH, "u_Shininess_Strength"}
};

TakeOne::Material::Material(std::shared_ptr<Program> pProgram)
        : mProgram(pProgram)
{
}

void TakeOne::Material::SetProgram(std::shared_ptr<Program> pProgram)
{
    mProgram = pProgram;
}

void TakeOne::Material::SetTexture(Texture&& pTexture)
{
    mTextures.push_back(std::move(pTexture));
}

void TakeOne::Material::Use()
{
    assert(mProgram != nullptr && "The program from material must be set!");

    static unsigned int sLastProgramId = 0;
    if(!sLastProgramId || sLastProgramId != mProgram->GetLastProgramUsed())
    {
        mProgram->Use();
        sLastProgramId = mProgram->GetLastProgramUsed();
    }

    if(mTextures.empty())
        Texture::Unbind();

    int texNumber = 0;
    for(const auto& texture:mTextures)
    {
        glActiveTexture(GL_TEXTURE0 + texNumber);
        texture.Bind();
        texNumber++;
    }
}

void TakeOne::Material::ResendShaderParam(const std::string& pName)
{
    mShaderParams[pName]->SendToShader();
}

void TakeOne::Material::ResendShaderParam(DefaultPropertiesEnum pName)
{
    mShaderParams[kDefaultUniforms[pName]]->SendToShader();
}

void TakeOne::Material::ResendShaderParams()
{
    for (auto& kv : mShaderParams)
    {
        kv.second->SendToShader();
    }
}

void TakeOne::Material::ApplyDefaultProperties(const std::vector<unsigned int>& pPropsUsed, const DefaultProperties& pDefaultProps)
{
    assert(pPropsUsed.size() <= DefaultPropertiesEnum::Count && "The Material Default Properties header is not correct!");

    if(pPropsUsed[COLOR_AMBIENT])
        SetShaderParam(COLOR_AMBIENT, pDefaultProps.color_ambient);

    if(pPropsUsed[COLOR_DIFFUSE])
        SetShaderParam(COLOR_DIFFUSE, pDefaultProps.color_diffuse);

    if(pPropsUsed[COLOR_EMISSIVE])
        SetShaderParam(COLOR_EMISSIVE, pDefaultProps.color_emissive);

    if(pPropsUsed[COLOR_REFLECTIVE])
        SetShaderParam(COLOR_REFLECTIVE, pDefaultProps.color_reflective);

    if(pPropsUsed[COLOR_SPECULAR])
        SetShaderParam(COLOR_SPECULAR, pDefaultProps.color_specular);

    if(pPropsUsed[COLOR_TRANSPARENT])
        SetShaderParam(COLOR_TRANSPARENT, pDefaultProps.color_transparent);

    if(pPropsUsed[OPACITY])
        SetShaderParam(OPACITY, pDefaultProps.opacity);

    if(pPropsUsed[REFLECTIVITY])
        SetShaderParam(REFLECTIVITY, pDefaultProps.reflectivity);

    if(pPropsUsed[REFRACTIVITY])
        SetShaderParam(REFRACTIVITY, pDefaultProps.refractivity);

    if(pPropsUsed[SHININESS])
        SetShaderParam(SHININESS, pDefaultProps.shininess);

    if(pPropsUsed[SHININESS_STRENGTH])
        SetShaderParam(SHININESS_STRENGTH, pDefaultProps.shininess_strength);
}

void TakeOne::Material::Reload()
{
    assert(mProgram != nullptr && "The program from material must be set!");

    mProgram->Reload();
    ResendShaderParams();
}

int TakeOne::Material::GetTexturesCount()
{
    return mTextures.size();
}
