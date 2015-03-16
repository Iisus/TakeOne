#include "RenderNode.h"

TakeOne::RenderNode::RenderNode(std::shared_ptr<RenderObject> pRenderObject)
        : mRenderObject(pRenderObject)
{

}

TakeOne::RenderNode::RenderNode(RenderNode&& pOther)
        : Node(std::move(pOther)), mRenderObject(std::move(pOther.mRenderObject))
{

}

TakeOne::RenderNode& TakeOne::RenderNode::operator= (RenderNode&& pOther)
{
    if(this != &pOther)
    {
        Node::operator=(std::move(pOther));
        mRenderObject = std::move(pOther.mRenderObject);
    }
    return *this;
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
        mRenderObject->GetMaterial().SetShaderParam(pUniformName, mTransform->GetTransformMatrix());
}
