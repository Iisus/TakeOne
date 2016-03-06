#pragma once

#include "SampleUtil.h"
#include "StateSample.h"

class StateCube : public StateSample
{
public:

    StateCube(Engine* pEngine);

    virtual void Enter();

private:
    void SetupBoxNode();
};
