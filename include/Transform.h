#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include <vector>

namespace TakeOne
{
    class Transform
    {
    public:
        Transform(Transform* const pParent = nullptr);
        Transform(const Transform&) = delete;
        Transform& operator=(const Transform&) = delete;
        ~Transform();

        void SetParent(Transform* const pParent);
        Transform* const GetParent() const;
        void AddChild(Transform* const pChild);
        void RemoveChild(Transform* const);
        const std::vector<Transform*>& GetChildren() const;

        glm::mat4 GetTransformMatrix();
        glm::mat4 GetLocalTransformMatrix() const;

        void SetPosition(const glm::vec3& pPosition);
        void SetScale(const glm::vec3& pScale);
        void SetRotation(const glm::quat& pRotation);

        glm::vec3 GetPosition() const;
        glm::vec3 GetScale() const;
        glm::quat GetRotation() const;

    private:
        void UpdateIfDirty();
        void SetDirty();

        glm::mat4 mWorldTransform;

        glm::vec3 mPosition;
        glm::vec3 mScale;
        glm::quat mRotation;

        bool mDirty;

        Transform* mParent;
        std::vector<Transform*> mChildren;
    };
}
