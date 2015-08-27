#include "StateCube.h"
#include "Primitives.h"
#include "DefaultRes.h"

StateCube::StateCube(Engine *pEngine)
    : StateSample(pEngine)
{
    mCameraMoveSpeed = 0.2;

    DefaultRes defaultRes(SampleUtil::RES_FOLDER);
    mProgram = std::shared_ptr<Program>(std::move(defaultRes.SimpleTextureProgram()));

    SetupBoxNode();
}

void StateCube::SetupBoxNode()
{
    auto boxNode = make_unique<RenderNode>(make_shared<BoxRenderObject>(mProgram));

    Texture diffuseTx(SampleUtil::RES_FOLDER + "textures/container2.png", Texture::INVERT_Y | Texture::COMPRESS_TO_DXT | Texture::TEXTURE_REPEATS | Texture::MIPMAPS);

    boxNode->GetRenderObject()->GetMaterial().SetTexture(std::move(diffuseTx));

    boxNode->GetTransform()->SetScale(glm::vec3(1.0f));
    boxNode->GetTransform()->SetPosition(glm::vec3(0.0f,0.0f, -5.0f));

    AddObject("Cube", move(boxNode));
}
