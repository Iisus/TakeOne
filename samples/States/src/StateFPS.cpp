#include "StateFPS.h"
#include "DefaultRes.h"

const string StateFPS::kObjName = "Old_Man";

StateFPS::StateFPS(Engine *pEngine)
    : StateSample(pEngine)
{
    mCameraMoveSpeed = 5;

    DefaultRes defaultRes(SampleUtil::RES_FOLDER);
    mProgram = std::shared_ptr<Program>(std::move(defaultRes.SimpleTextureProgram()));

    LoadObject(kObjName);

    for(const auto& node : mObjects[kObjName])
    {
        mOldManTransform.AddChild(&node->GetTransform());
    }

    mOldManTransform.SetPosition(vec3(0, -145, -200));
    mOldManTransform.SetRotation(angleAxis(radians(180.0f), vec3(0, 1, 0)) * angleAxis(radians(-20.0f), vec3(1, 0, 0)));

    mCamera.GetTransform().AddChild(&mOldManTransform);

    LoadObject("House02");
}
