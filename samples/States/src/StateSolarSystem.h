#pragma once

#include "SampleUtil.h"
#include "StateSample.h"

class StateSolarSystem : public StateSample
{
private:

    struct PlanetProp
    {
        string Name;
        string Texture;
        float Radius;
        float Distance;
        float RotSpeed;
        float RevSpeed;
        float RotAcc;
        float RevAcc;
    };

public:
    StateSolarSystem(Engine* pEngine);

    virtual void Enter();
    virtual void Exit();
    virtual void Update();
    virtual void HandleEvents();

private:
    void SetupNode(const PlanetProp& pPlanet);

    unordered_map<string, PlanetProp> mPlanets;
    unordered_map<string, Transform> mTransformations;

};
