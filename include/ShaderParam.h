#pragma once

#include <typeindex>

namespace TakeOne
{
    //Use as base for ShaderParam so it can be used in std::vector
    class ShaderParamBase
    {
    public:
        virtual ~ShaderParamBase();

        virtual int GetId() = 0;
        virtual std::type_index GetTypeIndex() = 0;
        virtual int GetCount() = 0;
        virtual void* GetValue() = 0;
    };

    template<typename T>
    class ShaderParam : public ShaderParamBase
    {
    public:
        ShaderParam(int pId, T pValue, int pCount);
        int GetId();
        std::type_index GetTypeIndex();
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
