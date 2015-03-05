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
        CameraNode();
        CameraNode(CameraType pCameraType);
        ~CameraNode();

        inline void SetCameraType(CameraType pCameraType) { mCameraType = pCameraType; }
        inline CameraType GetCameraType() const { return mCameraType; }

        void SetClearColor(const glm::vec4& pClearColor);
        const glm::vec4 GetClearColor() const { return mClearColor; }

        void SetAngleAxis(const glm::vec4& pAngleAxis);
        void SetAngleAxis(float pAngle, const glm::vec3& pAxis);
        glm::vec4 GetAngleAxis() const;
        float GetAngle() const;
        glm::vec3 GetAxis() const;
        void Rotate(const glm::vec4& pAngleAxis);
        void Rotate(float pAngle, const glm::vec3& pAxis);

        void LookAt(const glm::vec3& pLookAt, const glm::vec3& pUp = glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 GetFrontDir();
        glm::vec3 GetUpDir();
        glm::vec3 GetRightDir();

        void SetPerspective(float pFOV, float pAspectRatio, float pNearPlane, float pFarPlane);
        void SetOrthographic(float pLeft, float pRight, float pTop, float pBottom, float pNearPlane, float pFarPlane);

        inline float GetNearPlane() { return mNearPlane; }
        inline float GetFarPlane() { return mFarPlane; }
        inline float GetFOV() { assert(mCameraType == CameraType::PERSPECTIVE); return mFOV; }
        inline float GetAspectRatio() { assert(mCameraType == CameraType::PERSPECTIVE); return mAspectRatio; }
        inline float GetLeft() { assert(mCameraType == CameraType::ORTHOGRAPHIC); return mLeft; }
        inline float GetRight() { assert(mCameraType == CameraType::ORTHOGRAPHIC); return mRight; }
        inline float GetTop() { assert(mCameraType == CameraType::ORTHOGRAPHIC); return mTop; }
        inline float GetBottom() { assert(mCameraType == CameraType::ORTHOGRAPHIC); return mBottom; }

        inline glm::mat4 GetViewMatrix() { return glm::inverse(mTransform.GetTransformMatrix()); }
        inline glm::mat4 GetProjectionMatrix() { return mProjection; }
        inline glm::mat4 GetViewProjectionMatrix() { return mProjection * glm::inverse(mTransform.GetTransformMatrix()); }

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
