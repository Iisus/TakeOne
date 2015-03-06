#include "Transform.h"
#include "glm/gtx/transform.hpp"
#include <algorithm>

TakeOne::Transform::Transform(Transform* const pParent)
        : mWorldTransform(glm::mat4()), mPosition(glm::vec3(0.0f)), mScale(glm::vec3(1.0f)), mRotation(glm::quat()), mDirty(true), mParent(pParent)
{

}

TakeOne::Transform::~Transform()
{

}

void TakeOne::Transform::SetParent(TakeOne::Transform* const pParent)
{
    if(mParent)
    {
        mParent->RemoveChild(this);
    }

    if(pParent)
    {
        pParent->AddChild(this);
    }
}

TakeOne::Transform* const TakeOne::Transform::GetParent() const
{
    return mParent;
}

void TakeOne::Transform::AddChild(Transform* const pChild)
{
    mChildren.push_back(pChild);
    if(pChild->GetParent())
    {
        pChild->SetParent(nullptr);
    }
    pChild->mParent = this;
}

void TakeOne::Transform::RemoveChild(TakeOne::Transform* const pChild)
{
    mChildren.erase(std::remove(mChildren.begin(), mChildren.end(), pChild), mChildren.end());
    pChild->mParent = nullptr;
}

const std::vector<TakeOne::Transform*>& TakeOne::Transform::GetChildren() const
{
    return mChildren;
}


glm::mat4 TakeOne::Transform::GetTransformMatrix()
{
    UpdateIfDirty();
    return mWorldTransform;
}

glm::mat4 TakeOne::Transform::GetLocalTransformMatrix() const
{
    return glm::translate(mPosition) * glm::mat4_cast(mRotation) * glm::scale(mScale);
}

void TakeOne::Transform::SetPosition(const glm::vec3& pPosition)
{
    SetDirty();
    mPosition = pPosition;
}

void TakeOne::Transform::SetScale(const glm::vec3& pScale)
{
    SetDirty();
    mScale = pScale;
}

void TakeOne::Transform::SetRotation(const glm::quat& pRotation)
{
    SetDirty();
    mRotation = pRotation;
}

glm::vec3 TakeOne::Transform::GetPosition() const
{
    return mPosition;
}

glm::vec3 TakeOne::Transform::GetScale() const
{
    return mScale;
}

glm::quat TakeOne::Transform::GetRotation() const
{
    return mRotation;
}

void TakeOne::Transform::UpdateIfDirty()
{
    if(mDirty)
    {
        if(mParent)
        {
            mParent->UpdateIfDirty();
            mWorldTransform = mParent->mWorldTransform * GetLocalTransformMatrix();
        }
        else
        {
            mWorldTransform = GetLocalTransformMatrix();
        }

        mDirty = false;
    }
}

void TakeOne::Transform::SetDirty()
{
    mDirty = true;
    for(auto child : mChildren)
    {
        child->SetDirty();
    }
}
