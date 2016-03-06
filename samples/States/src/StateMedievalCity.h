#pragma once

#include "SampleUtil.h"
#include "StateSample.h"

class StateMedievalCity : public StateSample
{
public:
    StateMedievalCity(Engine* pEngine);

    virtual void Enter();
    virtual void Update();
};
