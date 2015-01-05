#pragma once

#include "Node.h"
#include "RenderObject.h"
#include <memory>

namespace TakeOne
{
    class RenderNode : public Node
    {
    public:
        RenderNode();
        RenderNode(std::shared_ptr<RenderObject> pRenderObject);
        ~RenderNode();

        void SetRenderObject(std::shared_ptr<RenderObject> pRenderObject);
        std::shared_ptr<RenderObject> GetRenderObject();

        void ApplyTransformation(const std::string& pUniformName);
    private:
        std::shared_ptr<RenderObject> mRenderObject;
    };
}
