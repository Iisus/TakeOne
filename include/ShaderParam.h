#pragma once

namespace TakeOne
{
    //Use as base for ShaderParam so it can be used in std::vector
    class ShaderParamBase
    {
    public:
        virtual ~ShaderParamBase();

        virtual int GetId() = 0;
        virtual unsigned long GetTypeHash() = 0;
        virtual int GetCount() = 0;
        virtual void* GetValue() = 0;
    };

    template<typename T>
    class ShaderParam : public ShaderParamBase
    {
    public:
        ShaderParam(int pId, T pValue, int pCount);
        int GetId();
        unsigned long GetTypeHash();
        int GetCount();
        void* GetValue();
        void SetValue(T pValue);

    private:
        int mId;
        int mCount;
        T mValue;
    };
}

#include "template_impl/ShaderParam.hpp"
