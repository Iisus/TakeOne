#include "Node.h"

unsigned int TakeOne::Node::sIndex = 0;

TakeOne::Node::Node()
{
    mTransform.reset(new Transform);
    mName = "Node_" + std::to_string(sIndex);
    sIndex++;
}

TakeOne::Node::Node(Node&& pOther) :
        mTransform(std::move(pOther.mTransform)), mName(std::move(pOther.mName))
{

}

TakeOne::Node& TakeOne::Node::operator= (Node&& pOther)
{
    if(this != &pOther)
    {
        mName = std::move(pOther.mName);
        mTransform = std::move(pOther.mTransform);
    }
    return *this;
}

TakeOne::Node::~Node()
{

}

void TakeOne::Node::SetName(const std::string& pName)
{
    mName = pName;
}

std::string TakeOne::Node::GetName() const
{
    return mName;
}

TakeOne::Transform& TakeOne::Node::GetTransform()
{
    return *mTransform;
}
