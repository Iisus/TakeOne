#pragma once

#include "Node.h"
#include "RenderObject.h"
#include <memory>

namespace TakeOne
{
    class RenderNode : public Node
    {
    public:
        RenderNode(std::shared_ptr<RenderObject> pRenderObject = nullptr);
        RenderNode(const RenderNode&) = delete;
        RenderNode& operator= (const RenderNode&) = delete;
        RenderNode(RenderNode&&);
        RenderNode& operator= (RenderNode&&);
        ~RenderNode();

        void SetRenderObject(std::shared_ptr<RenderObject> pRenderObject);
        std::shared_ptr<RenderObject> GetRenderObject();

        void SendModelMatrix();
    private:
        std::shared_ptr<RenderObject> mRenderObject;

        static const std::string kModelUniformName;
    };
}
