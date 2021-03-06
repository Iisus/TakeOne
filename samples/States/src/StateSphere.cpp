#include "StateSphere.h"
#include "Primitives.h"
#include "DefaultRes.h"

StateSphere::StateSphere(Engine *pEngine)
    : StateSample(pEngine)
{
    mCameraMoveSpeed = 0.2;

    DefaultRes defaultRes(SampleUtil::RES_FOLDER);
    mProgram = std::shared_ptr<Program>(std::move(defaultRes.SimpleTextureProgram()));

    SetupSphereNode();
}

void StateSphere::SetupSphereNode()
{
    auto sphereNode = make_unique<RenderNode>(make_shared<SphereRenderObject>(mProgram, 1, 100, 100));

    Texture diffuseTx(SampleUtil::RES_FOLDER + "textures/SolarSystem/texture_saturn_ring.png", Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS);

    sphereNode->GetRenderObject()->GetMaterial().SetTexture(std::move(diffuseTx));

    sphereNode->GetTransform()->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
    sphereNode->GetTransform()->SetPosition(glm::vec3(0.0f,0.0f, -5.0f));

    //mCamera.GetTransform().AddChild(&sphereNode->GetTransform(), Transform::TRANSLATION);

    AddObject("Sphere", move(sphereNode));
}
