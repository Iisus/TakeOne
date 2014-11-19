#include "ShaderParam.h"

#include "glm/gtc/type_ptr.hpp"
#include <string>
#include <typeinfo>

template<typename T>
TakeOne::ShaderParam<T>::ShaderParam(int pId, T pValue, int pCount)
        : mId(pId), mCount(pCount), mValue(pValue)
{
}

template<typename T>
int TakeOne::ShaderParam<T>::GetId()
{
    return mId;
}

template<typename T>
unsigned long TakeOne::ShaderParam<T>::GetTypeHash()
{
    return typeid(T).hash_code();
}

template<typename T>
int TakeOne::ShaderParam<T>::GetCount()
{
    return mCount;
}

template<typename T>
void* TakeOne::ShaderParam<T>::GetValue()
{
    return  (std::is_fundamental<T>::value) ? static_cast<void*>(&mValue) : static_cast<void*>(glm::value_ptr(mValue));
}

template<typename T>
void TakeOne::ShaderParam<T>::SetValue(T pValue)
{
    mValue = pValue;
}
