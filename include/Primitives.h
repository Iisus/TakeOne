#pragma once

#include "RenderObject.h"

namespace TakeOne
{
    class BoxRenderObject : public RenderObject
    {
    public:
        BoxRenderObject(const std::shared_ptr<Program>& pProgram);
    };

    class PlaneRenderObject : public RenderObject
    {
    public:
        PlaneRenderObject(const std::shared_ptr<Program>& pProgram);
    };
}
