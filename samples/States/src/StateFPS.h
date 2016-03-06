#pragma once

#include "SampleUtil.h"
#include "StateSample.h"

class StateFPS : public StateSample
{
public:
    StateFPS(Engine* pEngine);

private:
    Transform mOldManTransform;
    static const string kObjName;

};
