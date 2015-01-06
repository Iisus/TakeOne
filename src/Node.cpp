#include "Node.h"

unsigned int TakeOne::Node::sIndex = 0;

TakeOne::Node::Node()
{
    mName = "Node_" + std::to_string(sIndex);
    sIndex++;
}

TakeOne::Node::~Node()
{

}

void TakeOne::Node::SetName(const std::string& pName)
{
    mName = pName;
}

std::string TakeOne::Node::GetName()
{
    return mName;
}

TakeOne::Transform& TakeOne::Node::GetTransform()
{
    return mTransform;
}
