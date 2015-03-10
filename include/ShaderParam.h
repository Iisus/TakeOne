#pragma once

namespace TakeOne
{
    //Use as base for ShaderParam so it can be used in std::vector
    class ShaderParamBase
    {
    public:
        virtual ~ShaderParamBase();
        virtual void SendToShader() = 0;
    };

    template<typename T>
    class ShaderParam : public ShaderParamBase
    {
    public:
        ShaderParam(int pId, T pValue, int pCount);
        void SendToShader();
        void SetValue(T pValue);

    private:
        int mId;
        int mCount;
        T mValue;
    };
}

#include "template_impl/ShaderParam.hpp"
