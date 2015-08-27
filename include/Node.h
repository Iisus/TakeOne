#pragma once

#include "Transform.h"
#include <string>
#include <memory>

namespace TakeOne
{
    class Node
    {
    public:
        Node();
        Node(const Node&) = delete;
        Node& operator= (const Node&) = delete;
        Node(Node&&);
        Node& operator= (Node&&);
        virtual ~Node();

        void SetName(const std::string& pName);
        std::string GetName() const;

        Transform* GetTransform();

    protected:
        std::unique_ptr<Transform> mTransform;
        std::string mName;

    private:
        static unsigned int sIndex;
    };
}
