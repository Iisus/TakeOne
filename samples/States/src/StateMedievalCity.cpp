#include "StateMedievalCity.h"
#include "DefaultRes.h"
#include "LightNode.h"
#include "Primitives.h"

StateMedievalCity::StateMedievalCity(Engine *pEngine)
    : StateSample(pEngine)
{
    mCameraMoveSpeed = 1;

    DefaultRes defaultRes(SampleUtil::RES_FOLDER);
    mProgram = std::shared_ptr<Program>(std::move(defaultRes.SpecularMapProgram()));

    LoadObject("Medieval_City");

    for(const auto& objects: mObjects)
        for(const auto& node : objects.second)
        {
            node->GetRenderObject()->GetMaterial().SetShaderParam("u_Shininess", 0.6f);
            node->GetTransform()->SetPosition(vec3(10, -45, 0));
        }
}

void StateMedievalCity::Enter()
{
    StateSample::Enter();

    LightNode light(LightType::POINT);
    light.SetupPoint(vec3(1000.0), vec3(0.3, 0.6, 0.9), vec3(0.8, 0.7, 0.1), vec3(1.0, 1.0, 0.6), 0.1, 100.0);

    auto boxNode = make_unique<RenderNode>(make_shared<BoxRenderObject>(mProgram));
    boxNode->GetTransform()->SetParent(light.GetTransform(), Transform::Transofmations::TRANSLATION);
    boxNode->GetTransform()->SetScale(vec3(30));

    AddObject("LightModel", move(boxNode));
    mLights.push_back(move(light));

    glDisable(GL_CULL_FACE);
}

void StateMedievalCity::Update()
{
    StateSample::Update();
    static double lightPos = 0;

    for(auto& light : mLights)
    {
        light.GetTransform()->SetPosition(vec3(sin(lightPos) - 0.5, 1, cos(lightPos) - 0.5) * 1000.0f);
    }

    lightPos += 0.01;
}
