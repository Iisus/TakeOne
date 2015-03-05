#pragma once

#include "Transform.h"
#include <string>

namespace TakeOne
{
    class Node
    {
    public:
        Node();
        Node(const Node&) = delete;
        Node& operator= (const Node&) = delete;
        virtual ~Node();

        void SetName(const std::string& pName);
        std::string GetName();

        Transform& GetTransform();

    protected:
        Transform mTransform;
        std::string mName;

    private:
        static unsigned int sIndex;
    };
}
