#include "ShaderParam.h"
#include <string>

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
std::type_index TakeOne::ShaderParam<T>::GetTypeIndex()
{
    return std::type_index(typeid(T));
}

template<typename T>
int TakeOne::ShaderParam<T>::GetCount()
{
    return mCount;
}

template<typename T>
void* TakeOne::ShaderParam<T>::GetValue()
{
    return &mValue;
}

template<typename T>
void TakeOne::ShaderParam<T>::SetValue(T pValue)
{
    mValue = pValue;
}
