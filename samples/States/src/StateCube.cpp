#include "StateCube.h"
#include "Primitives.h"
#include "DefaultRes.h"

StateCube::StateCube(Engine *pEngine)
    : StateSample(pEngine)
{
    mCameraMoveSpeed = 0.2;

    DefaultRes defaultRes(SampleUtil::RES_FOLDER);
    mProgram = std::shared_ptr<Program>(std::move(defaultRes.SpecularMapProgram()));

    SetupBoxNode();
}

void StateCube::SetupBoxNode()
{
    auto boxNode = make_unique<RenderNode>(make_shared<BoxRenderObject>(mProgram));

    Texture diffuseTx(SampleUtil::RES_FOLDER + "textures/container2.png", Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS, 0);
    Texture specularTx(SampleUtil::RES_FOLDER + "textures/container2_specular.png", Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS, 1);

    boxNode->GetRenderObject()->GetMaterial().SetTexture(std::move(diffuseTx), "u_DiffuseMap");
    boxNode->GetRenderObject()->GetMaterial().SetTexture(std::move(specularTx), "u_SpecularMap");

    boxNode->GetTransform()->SetScale(glm::vec3(1.0f));
    boxNode->GetTransform()->SetPosition(glm::vec3(0.0f,0.0f, -5.0f));

    boxNode->GetRenderObject()->GetMaterial().SetShaderParam("u_Shininess", 0.6f);

    AddObject("Cube", move(boxNode));
}

void StateCube::Enter()
{
    StateSample::Enter();

    LightNode light(LightType::POINT);
    light.SetupPoint(vec3(10.0), vec3(1.0), vec3(1.0), vec3(1.0), 0.1, 100.0);
    mLights.push_back(move(light));
}
