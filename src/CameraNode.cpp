#include "CameraNode.h"
#include "glm/gtx/transform.hpp"
#include <glm/gtx/euler_angles.hpp>
#include <GL/glew.h>

TakeOne::CameraNode::CameraNode(TakeOne::CameraType pCameraType)
        : mCameraType(pCameraType), mNearPlane(0.0f), mFarPlane(100.0f), mFOV(45.0f), mAspectRatio(4.0f/3.0f),
          mLeft(-1.0f), mRight(1.0f), mBottom(-1.0f), mTop(1.0f), mProjection(0.0f)
{

}

TakeOne::CameraNode::~CameraNode()
{

}

void TakeOne::CameraNode::SetClearColor(const glm::vec4& pClearColor)
{
    mClearColor = pClearColor;
    glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);
}

glm::vec4 TakeOne::CameraNode::GetClearColor() const
{
    return mClearColor;
}

void TakeOne::CameraNode::SetAngleAxis(const glm::vec4& pAngleAxis)
{
    mTransform->SetRotation(glm::angleAxis(pAngleAxis.x, glm::vec3(pAngleAxis.y, pAngleAxis.z, pAngleAxis.w)));
}

void TakeOne::CameraNode::SetAngleAxis(float pAngle, const glm::vec3& pAxis)
{
    mTransform->SetRotation(glm::angleAxis(pAngle, pAxis));
}

glm::vec4 TakeOne::CameraNode::GetAngleAxis() const
{
    auto quat = mTransform->GetRotation();
    return glm::vec4(glm::angle(quat), glm::axis(quat));
}

float TakeOne::CameraNode::GetAngle() const
{
    return glm::angle(mTransform->GetRotation());
}

glm::vec3 TakeOne::CameraNode::GetAxis() const
{
    return glm::axis(mTransform->GetRotation());
}

void TakeOne::CameraNode::Rotate(const glm::vec4& pAngleAxis)
{
    mTransform->SetRotation(
        mTransform->GetRotation() * glm::angleAxis(pAngleAxis.x, glm::vec3(pAngleAxis.y, pAngleAxis.z, pAngleAxis.w))
    );
}

void TakeOne::CameraNode::Rotate(float pAngle, const glm::vec3& pAxis)
{
    mTransform->SetRotation(mTransform->GetRotation() * glm::angleAxis(pAngle, pAxis));
}

void TakeOne::CameraNode::LookAt(const glm::vec3& pLookAt, const glm::vec3& pUp)
{
    mTransform->SetRotation(
        glm::toQuat(
            glm::lookAt(
                mTransform->GetPosition(),
                pLookAt,
                pUp
            )
        )
    );
}

glm::vec3 TakeOne::CameraNode::GetFrontDir() const
{
    return glm::normalize(glm::mat3_cast(mTransform->GetRotation())[2]);
}

glm::vec3 TakeOne::CameraNode::GetUpDir() const
{
    return glm::normalize(glm::mat3_cast(mTransform->GetRotation())[1]);
}

glm::vec3 TakeOne::CameraNode::GetRightDir() const
{
    return glm::normalize(glm::mat3_cast(mTransform->GetRotation())[0]);
}

void TakeOne::CameraNode::SetPerspective(float pFOV, float pAspectRatio, float pNearPlane, float pFarPlane)
{
    assert(mCameraType == CameraType::PERSPECTIVE);
    mFOV = pFOV;
    mAspectRatio = pAspectRatio;
    mNearPlane = pNearPlane;
    mFarPlane = pFarPlane;

    mProjection = static_cast<glm::mat4>(glm::perspective(pFOV, pAspectRatio, pNearPlane, pFarPlane));
}

void TakeOne::CameraNode::SetOrthographic(float pLeft, float pRight, float pTop, float pBottom, float pNearPlane, float pFarPlane)
{
    assert(mCameraType == CameraType::ORTHOGRAPHIC);
    mLeft = pLeft;
    mRight = pRight;
    mBottom = pBottom;
    mTop = pTop;
    mNearPlane = pNearPlane;
    mFarPlane = pFarPlane;

    mProjection = static_cast<glm::mat4>(glm::ortho(pLeft, pRight, pBottom, pTop, pNearPlane, pFarPlane));
}
