#pragma once

#include "Program.h"
#include "GL/glew.h"
#include <string>
#include <vector>
#include <map>

namespace TakeOne
{
    enum class ShaderParamType
    {
        UNIFORM_1f,
        UNIFORM_2f,
        UNIFORM_3f,
        UNIFORM_4f,

        UNIFORM_M2x2f,
        UNIFORM_M3x3f,
        UNIFORM_M4x4f,
        UNIFORM_M2x3f,
        UNIFORM_M3x2f,
        UNIFORM_M2x4f,
        UNIFORM_M4x2f,
        UNIFORM_M3x4f,
        UNIFORM_M4x3f,
    };

    struct ShaderParam
    {
        ShaderParam(int _id, ShaderParamType _type, std::string _name, const float* _value, int _count)
                : id(_id), type(_type), name(_name), value(_value), count(_count)
        {}

        int id;
        ShaderParamType type;
        std::string name;
        const float* value;
        int count;
    };

    class Material
    {
    public:
        Material(std::unique_ptr<Program> pProgram);
        void SetParam(ShaderParamType pType, const std::string& pName, const float* pValue, int pCount = 1);

    private:
        std::unique_ptr<Program> mProgram;
        std::vector<ShaderParam> mShaderParams;
    };
}