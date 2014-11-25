#include "MaterialLoader.h"

void TakeOne::MaterialLoader::Apply(Material& pMaterial)
{
    unsigned long uniformIndex = 0;

    if(mFormatsUsed[uniformIndex++])
        pMaterial.SetShaderParam("u_color_ambient", mMaterialFormat.color_ambient);

    if(mFormatsUsed[uniformIndex++])
        pMaterial.SetShaderParam("u_color_diffuse", mMaterialFormat.color_diffuse);

    if(mFormatsUsed[uniformIndex++])
        pMaterial.SetShaderParam("u_color_emissive", mMaterialFormat.color_emissive);

    if(mFormatsUsed[uniformIndex++])
        pMaterial.SetShaderParam("u_color_reflective", mMaterialFormat.color_reflective);

    if(mFormatsUsed[uniformIndex++])
        pMaterial.SetShaderParam("u_color_specular", mMaterialFormat.color_specular);

    if(mFormatsUsed[uniformIndex++])
        pMaterial.SetShaderParam("u_color_transparent", mMaterialFormat.color_transparent);

    if(mFormatsUsed[uniformIndex++])
        pMaterial.SetShaderParam("u_opacity", mMaterialFormat.opacity);

    if(mFormatsUsed[uniformIndex++])
        pMaterial.SetShaderParam("u_reflectivity", mMaterialFormat.reflectivity);

    if(mFormatsUsed[uniformIndex++])
        pMaterial.SetShaderParam("u_refractivity", mMaterialFormat.refractivity);

    if(mFormatsUsed[uniformIndex++])
        pMaterial.SetShaderParam("u_shininess", mMaterialFormat.shininess);

    if(mFormatsUsed[uniformIndex])
        pMaterial.SetShaderParam("u_shininess_strength", mMaterialFormat.shininess_strength);

    //when insert new values, be carefull, uniformIndex is not incremented at the last if
}

void TakeOne::MaterialLoader::SetMaterialFormat(MaterialFormat&& pMaterialFormat)
{
    mMaterialFormat = std::move(pMaterialFormat);
}

void TakeOne::MaterialLoader::SetFormatUsed(std::vector<unsigned int> pFormatsUsed)
{
    mFormatsUsed = std::move(pFormatsUsed);
}
