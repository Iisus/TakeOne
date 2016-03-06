#pragma once

#include "SampleUtil.h"
#include "StateSample.h"

class StateObjects : public StateSample
{
public:
    StateObjects(Engine* pEngine, const string &pScene);

    virtual void Enter();
    virtual void Update();
};
