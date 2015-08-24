#pragma once

#include "SampleUtil.h"
#include "StateSample.h"

class StateCube : public StateSample
{
public:

    StateCube(Engine* pEngine);

private:
    void SetupBoxNode();
};
