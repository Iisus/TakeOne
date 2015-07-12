#include "MaterialHelper.h"

void TakeOne::MaterialHelper::Apply(Material& pMaterial)
{
    if(mFormatsUsed[COLOR_AMBIENT])
        pMaterial.SetShaderParam("u_color_ambient", mMaterialFormat.color_ambient);

    if(mFormatsUsed[COLOR_DIFFUSE])
        pMaterial.SetShaderParam("u_color_diffuse", mMaterialFormat.color_diffuse);

    if(mFormatsUsed[COLOR_EMISSIVE])
        pMaterial.SetShaderParam("u_color_emissive", mMaterialFormat.color_emissive);

    if(mFormatsUsed[COLOR_REFLECTIVE])
        pMaterial.SetShaderParam("u_color_reflective", mMaterialFormat.color_reflective);

    if(mFormatsUsed[COLOR_SPECULAR])
        pMaterial.SetShaderParam("u_color_specular", mMaterialFormat.color_specular);

    if(mFormatsUsed[COLOR_TRANSPARENT])
        pMaterial.SetShaderParam("u_color_transparent", mMaterialFormat.color_transparent);

    if(mFormatsUsed[OPACITY])
        pMaterial.SetShaderParam("u_opacity", mMaterialFormat.opacity);

    if(mFormatsUsed[REFLECTIVITY])
        pMaterial.SetShaderParam("u_reflectivity", mMaterialFormat.reflectivity);

    if(mFormatsUsed[REFRACTIVITY])
        pMaterial.SetShaderParam("u_refractivity", mMaterialFormat.refractivity);

    if(mFormatsUsed[SHININESS])
        pMaterial.SetShaderParam("u_shininess", mMaterialFormat.shininess);

    if(mFormatsUsed[SHININESS_STRENGTH])
        pMaterial.SetShaderParam("u_shininess_strength", mMaterialFormat.shininess_strength);

    pMaterial.SetShaderParam("u_textures_count", pMaterial.GetTexturesCount());
}

void TakeOne::MaterialHelper::SetMaterialFormat(MaterialFormat&& pMaterialFormat)
{
    mMaterialFormat = std::move(pMaterialFormat);
}

void TakeOne::MaterialHelper::SetFormatUsed(std::vector<unsigned int>&& pFormatsUsed)
{
    mFormatsUsed = std::move(pFormatsUsed);
}
