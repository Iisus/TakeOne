#pragma once

#define GLM_FORCE_RADIANS
#include "glm/gtc/type_ptr.hpp"
#include <string>

namespace TakeOne
{
    enum class ShaderParamType
    {
        UNIFORM_1f,
        UNIFORM_2f,
        UNIFORM_3f,
        UNIFORM_4f,

        UNIFORM_1i,
        UNIFORM_2i,
        UNIFORM_3i,
        UNIFORM_4i,

        UNIFORM_1ui,
        UNIFORM_2ui,
        UNIFORM_3ui,
        UNIFORM_4ui,

        UNIFORM_MATRIX, //used to check if the uniform is a matrix or a vector

        UNIFORM_2x2f,
        UNIFORM_3x3f,
        UNIFORM_4x4f,
        UNIFORM_2x3f,
        UNIFORM_3x2f,
        UNIFORM_2x4f,
        UNIFORM_4x2f,
        UNIFORM_3x4f,
        UNIFORM_4x3f,
    };

    //Use as base for ShaderParam so it can be used in std::vector
    struct ShaderParamBase
    {
        virtual ~ShaderParamBase() {};

        virtual const int GetId() = 0;
        virtual const ShaderParamType GetType() = 0;
        virtual const int GetCount() = 0;
        virtual const void* GetValue() = 0;
    };

    template<typename T>
    struct ShaderParam : ShaderParamBase
    {
        ShaderParam(int _id, ShaderParamType _type, std::string _name, T _value, int _count)
                : id(_id), type(_type), name(_name), value(_value), count(_count)
        {
        }

        const int GetId() {return id;};
        const ShaderParamType GetType() {return type;}
        const int GetCount() {return count;};
        const void* GetValue()
        {
            return  (type == ShaderParamType::UNIFORM_1f ||
                    type == ShaderParamType::UNIFORM_1i ||
                    type == ShaderParamType::UNIFORM_1ui) ? (void*)&value : (void*)glm::value_ptr(value);
        };

    private:
        int id;
        ShaderParamType type;
        std::string name;
        T value;
        int count;
    };

}