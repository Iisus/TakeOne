#pragma once

#include "SampleUtil.h"
#include "StateSample.h"

class StateSolarSystem : public StateSample
{
private:
    enum Planet
    {
        Sky,
        Sun,
        Mercury,
        Venus,
        Earth,
        Moon,
        Mars,
        Jupiter,
        Saturn,
        Uranus,
        Neptune,

        Count
    };

    struct PlanetProp
    {
        string Name;
        string Texture;
        float Radius;
        float Distance;
        float Speed;
    };

public:
    StateSolarSystem(Engine* pEngine);

    virtual void Update();
private:
    void SetupNode(const PlanetProp& pPlanet);

    vector<PlanetProp> mPlanets;
    Transform mSunTransform;

};
