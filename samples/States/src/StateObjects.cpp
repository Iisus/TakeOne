#include "StateObjects.h"
#include "DefaultRes.h"

StateObjects::StateObjects(Engine *pEngine, const std::string& pScene)
    : StateSample(pEngine)
{
    mCameraMoveSpeed = 5;

    DefaultRes defaultRes(SampleUtil::RES_FOLDER);
    mProgram = std::shared_ptr<Program>(std::move(defaultRes.SimpleTextureProgram()));

    LoadObject(pScene);
}
