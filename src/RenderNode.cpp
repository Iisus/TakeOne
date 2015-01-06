#include "RenderNode.h"

TakeOne::RenderNode::RenderNode()
        : mRenderObject(nullptr)
{

}

TakeOne::RenderNode::RenderNode(std::shared_ptr<RenderObject> pRenderObject)
        : mRenderObject(pRenderObject)
{

}

TakeOne::RenderNode::~RenderNode()
{

}

void TakeOne::RenderNode::SetRenderObject(std::shared_ptr<TakeOne::RenderObject> pRenderObject)
{
    mRenderObject = pRenderObject;
}

std::shared_ptr<TakeOne::RenderObject> TakeOne::RenderNode::GetRenderObject()
{
    return mRenderObject;
}

void TakeOne::RenderNode::ApplyTransformation(const std::string& pUniformName)
{
    if(mRenderObject)
        mRenderObject->GetMaterial().SetShaderParam(pUniformName, mTransform.GetTransform());
}
