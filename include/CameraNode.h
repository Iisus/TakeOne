#pragma once

#include "Node.h"

namespace TakeOne
{
    enum class CameraType
    {
        PERSPECTIVE,
        ORTHOGRAPHIC
    };

    class CameraNode : public Node
    {
    public:
        CameraNode(CameraType pCameraType = CameraType::PERSPECTIVE);
        ~CameraNode(); //empty

        void SetCameraType(CameraType pCameraType) { mCameraType = pCameraType; }
        CameraType GetCameraType() const { return mCameraType; }

        void SetClearColor(const glm::vec4& pClearColor);
        glm::vec4 GetClearColor() const;

        void SetAngleAxis(const glm::vec4& pAngleAxis);
        void SetAngleAxis(float pAngle, const glm::vec3& pAxis);
        glm::vec4 GetAngleAxis() const;
        float GetAngle() const;
        glm::vec3 GetAxis() const;
        void Rotate(const glm::vec4& pAngleAxis);
        void Rotate(float pAngle, const glm::vec3& pAxis);

        void LookAt(const glm::vec3& pLookAt, const glm::vec3& pUp = glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 GetFrontDir() const;
        glm::vec3 GetUpDir() const;
        glm::vec3 GetRightDir() const;

        void SetPerspective(float pFOV, float pAspectRatio, float pNearPlane, float pFarPlane);
        void SetOrthographic(float pLeft, float pRight, float pTop, float pBottom, float pNearPlane, float pFarPlane);

        float GetNearPlane() const { return mNearPlane; }
        float GetFarPlane() const { return mFarPlane; }
        float GetFOV() const { assert(mCameraType == CameraType::PERSPECTIVE); return mFOV; }
        float GetAspectRatio() const { assert(mCameraType == CameraType::PERSPECTIVE); return mAspectRatio; }
        float GetLeft() const { assert(mCameraType == CameraType::ORTHOGRAPHIC); return mLeft; }
        float GetRight() const { assert(mCameraType == CameraType::ORTHOGRAPHIC); return mRight; }
        float GetTop() const { assert(mCameraType == CameraType::ORTHOGRAPHIC); return mTop; }
        float GetBottom() const { assert(mCameraType == CameraType::ORTHOGRAPHIC); return mBottom; }

        inline glm::mat4 GetProjectionMatrix() const { return mProjection; }
        //non const because GetTransformMatrix updates it's members if dirty
        inline glm::mat4 GetViewMatrix() { return glm::inverse(mTransform->GetTransformMatrix()); }
        inline glm::mat4 GetViewProjectionMatrix() { return mProjection * glm::inverse(mTransform->GetTransformMatrix()); }

    private:

        CameraType mCameraType;

        glm::vec4 mClearColor;

        //for projection matrix:
        //common
        float mNearPlane;
        float mFarPlane;
        //perspective
        float mFOV;
        float mAspectRatio;
        //orthographic
        float mLeft;
        float mRight;
        float mBottom;
        float mTop;

        glm::mat4 mProjection;
        //view matrix is the matrix from the inherited transformation
    };
}
