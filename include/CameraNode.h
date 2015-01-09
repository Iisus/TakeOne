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
        inline CameraType GetCameraType() { return mCameraType; }

        void SetClearColor(const glm::vec4& pClearColor);
        inline glm::vec4 GetClearColor() { return mClearColor; }

        void SetYawPitchRoll(const glm::vec3& pYawPitchRoll);
        glm::vec3 GetYawPitchRoll();
        void SetYaw(float pYaw);
        float GetYaw();
        void SetPitch(float pPitch);
        float GetPitch();
        void SetRoll(float pRoll);
        float GetRoll();

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
