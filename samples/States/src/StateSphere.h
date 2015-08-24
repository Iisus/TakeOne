#pragma once

#include "SampleUtil.h"
#include "StateSample.h"

class StateSphere : public StateSample
{
public:

    StateSphere(Engine* pEngine);

private:
    void SetupSphereNode();
};
