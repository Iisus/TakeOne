#pragma once

#define GLM_FORCE_RADIANS
#include "glm/gtc/type_ptr.hpp"
#include <string>
#include <typeinfo>

namespace TakeOne
{
    //Use as base for ShaderParam so it can be used in std::vector
    struct ShaderParamBase
    {
        virtual ~ShaderParamBase() {};

        virtual const int GetId() = 0;
        virtual const unsigned int GetTypeHash() = 0;
        virtual const int GetCount() = 0;
        virtual void* GetValue() = 0;
    };

    template<typename T>
    struct ShaderParam : ShaderParamBase
    {
        ShaderParam(int _id, T _value, int _count)
                : mId(_id), mValue(_value), mCount(_count)
        {
        }

        const int GetId() {return mId;}
        const unsigned int GetTypeHash() {return typeid(T).hash_code();}
        const int GetCount() {return mCount;};
        void* GetValue()
        {
            return  (std::is_fundamental<T>::value) ? (void*)&mValue : (void*)glm::value_ptr(mValue);
        }

        void SetValue(T pValue)
        {
            mValue = pValue;
        }

    private:
        int mId;
        T mValue;
        int mCount;
    };

}