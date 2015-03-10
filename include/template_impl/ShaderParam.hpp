#include "ShaderParam.h"
#include <string>

template<typename T>
TakeOne::ShaderParam<T>::ShaderParam(int pId, T pValue, int pCount)
        : mId(pId), mCount(pCount), mValue(pValue)
{

}

template<typename T>
void TakeOne::ShaderParam<T>::SetValue(T pValue)
{
    mValue = pValue;
}
