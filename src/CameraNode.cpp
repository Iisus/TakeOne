#include "CameraNode.h"
#include "glm/gtx/transform.hpp"
#include <glm/gtx/euler_angles.hpp>
#include <GL/glew.h>

TakeOne::CameraNode::CameraNode()
        : CameraNode(CameraType::PERSPECTIVE)
{

}

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

void TakeOne::CameraNode::SetYawPitchRoll(const glm::vec3& pYawPitchRoll)
{
    mTransform.SetRotation(glm::toQuat(glm::orientate3(pYawPitchRoll)));
}

glm::vec3 TakeOne::CameraNode::GetYawPitchRoll()
{
    return glm::eulerAngles(mTransform.GetRotation());
}

void TakeOne::CameraNode::SetYaw(float pYaw)
{
    mTransform.SetRotation(
        glm::toQuat(
            glm::yawPitchRoll(
                pYaw,
                glm::pitch(mTransform.GetRotation()),
                glm::roll(mTransform.GetRotation())
            )
        )
    );
}

float TakeOne::CameraNode::GetYaw() const
{
    return glm::yaw(mTransform.GetRotation());
}

void TakeOne::CameraNode::SetPitch(float pPitch)
{
    mTransform.SetRotation(
        glm::toQuat(
            glm::yawPitchRoll(
                glm::yaw(mTransform.GetRotation()),
                pPitch,
                glm::roll(mTransform.GetRotation())
            )
        )
    );
}

float TakeOne::CameraNode::GetPitch() const
{
    return glm::pitch(mTransform.GetRotation());
}

void TakeOne::CameraNode::SetRoll(float pRoll)
{
    mTransform.SetRotation(
        glm::toQuat(
            glm::yawPitchRoll(
                glm::yaw(mTransform.GetRotation()),
                glm::pitch(mTransform.GetRotation()),
                pRoll
            )
        )
    );
}

float TakeOne::CameraNode::GetRoll() const
{
    return glm::roll(mTransform.GetRotation());
}

void TakeOne::CameraNode::LookAt(const glm::vec3& pLookAt, const glm::vec3& pUp)
{
    mTransform.SetRotation(
        glm::toQuat(
            glm::lookAt(
                mTransform.GetPosition(),
                pLookAt,
                pUp
            )
        )
    );
}

glm::vec3 TakeOne::CameraNode::GetFrontDir()
{
    return glm::normalize(glm::mat3_cast(mTransform.GetRotation()/2.0f)[0]);
}

glm::vec3 TakeOne::CameraNode::GetUpDir()
{
    return glm::normalize(glm::mat3_cast(mTransform.GetRotation()/2.0f)[1]);
}

glm::vec3 TakeOne::CameraNode::GetRightDir()
{
    return glm::normalize(glm::mat3_cast(mTransform.GetRotation()/2.0f)[2]);
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
