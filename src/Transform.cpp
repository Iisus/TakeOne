#include "Transform.h"
#include "glm/gtx/transform.hpp"
#include <algorithm>

TakeOne::Transform::Transform(Transform* const pParent) :
    mWorldTransform(glm::mat4()), mPosition(glm::vec3(0.0f)), mScale(glm::vec3(1.0f)), mRotation(glm::quat()), mDirty(true), mParent(pParent)
{

}

TakeOne::Transform::Transform(Transform&& pOther) :
    mWorldTransform(std::move(pOther.mWorldTransform)), mPosition(std::move(mPosition)), mScale(std::move(mScale)), mRotation(std::move(mRotation)),
    mDirty(std::move(pOther.mDirty)), mParent(pOther.mParent), mChildren(std::move(mChildren))
{
    pOther.mParent = nullptr;
}

TakeOne::Transform& TakeOne::Transform::operator=(Transform&& pOther)
{
    if(&pOther != this)
    {
        mWorldTransform = std::move(pOther.mWorldTransform);
        mPosition = std::move(mPosition);
        mScale = std::move(mScale);
        mRotation = std::move(mRotation);
        mDirty = std::move(pOther.mDirty);
        mParent = pOther.mParent;
        mChildren = std::move(mChildren);

        pOther.mParent = nullptr;
    }

    return *this;
}

TakeOne::Transform::~Transform()
{

}

void TakeOne::Transform::SetParent(TakeOne::Transform* const pParent, int pTransformations)
{
    if(mParent)
    {
        mParent->RemoveChild(this);
    }

    if(pParent)
    {
        pParent->AddChild(this, pTransformations);
    }
}

const TakeOne::Transform* TakeOne::Transform::GetParent() const
{
    return mParent;
}

void TakeOne::Transform::AddChild(Transform* const pChild, int pTransformations)
{
    mChildren.insert( {pChild, pTransformations} );
    if(pChild->GetParent())
    {
        pChild->SetParent(nullptr);
    }
    pChild->mParent = this;
}

void TakeOne::Transform::RemoveChild(TakeOne::Transform* const pChild)
{
    mChildren.erase(pChild);
    pChild->mParent = nullptr;
}

const std::vector<TakeOne::Transform*>& TakeOne::Transform::GetChildren() const
{
    std::vector<TakeOne::Transform*> ret;
    ret.reserve(mChildren.size());

    std::transform(mChildren.begin(), mChildren.end(), std::back_inserter(ret), [](auto elem){ return elem.first; });

    return std::move(ret);
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

            glm::mat4 worldTransform;

            int transforms = mParent->mChildren[this];
            if(transforms == 0)
            {
                worldTransform = mParent->mWorldTransform;
            }
            else
            {
                if(transforms & Transofmations::TRANSLATION)
                    worldTransform *= glm::translate(mParent->mPosition);
                if(transforms & Transofmations::ROTATION)
                    worldTransform *= glm::mat4_cast(mParent->mRotation);
                if(transforms & Transofmations::SCALE)
                    worldTransform *= glm::scale(mParent->mScale);
            }

            mWorldTransform = worldTransform * GetLocalTransformMatrix();
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
        child.first->SetDirty();
    }
}
