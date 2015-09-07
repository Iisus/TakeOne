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
        PlaneRenderObject(const std::shared_ptr<Program>& pProgram, glm::vec2 pTextureTile = glm::vec2(1.0f, 1.0f));
    };

    class SphereRenderObject : public RenderObject
    {
    public:
        SphereRenderObject(const std::shared_ptr<Program>& pProgram, float pRadius, int pRings, int pSectors);
    };
}
