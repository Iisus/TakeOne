#pragma once

#include "Shader.h"
#include <string>
#include <memory>

namespace TakeOne
{

    class Program
    {
    public:
        Program();
        Program(const std::string& pVertexPath, const std::string& pFragmentPath);
        Program(const Program&) = delete;
        Program& operator=(const Program&) = delete;
        Program(Program&&);
        Program& operator=(Program&&);
        ~Program();

        void Load(const std::string& pVertexPath, const std::string& pFragmentPath);
        void Reload();
        void Unload();
        void Use() const;
        int GetUniformLocation(const std::string& pName) const;

        inline unsigned int GetLastProgramUsed() { return mProgramId; }
    private:
        void Link();

        std::unique_ptr<Shader> mVertex;
        std::unique_ptr<Shader> mFragment;
        unsigned int mProgramId;
    };
}
