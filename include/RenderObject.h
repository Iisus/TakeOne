#pragma once

#include "Mesh.h"
#include "Material.h"
#include <string>
#include <fstream>

namespace TakeOne
{
    class RenderObject
    {
    public:
        RenderObject(std::shared_ptr<Program> pProgram = nullptr);
        RenderObject(std::shared_ptr<Program> pProgram, const std::string& pObjPath, const std::string& pObjName);

        void SetProgram(std::shared_ptr<Program> pProgram);

        void Load(const std::string& pObjPath, const std::string& pObjName);
        void Render() const;

        Mesh& GetMesh() const { return *mMesh; }
        Material& GetMaterial() const { return *mMaterial; }

        bool IsRenderable() const { return mRenderable; }
        void SetRenderable(bool pRenderable) { mRenderable = pRenderable; }

    protected:
        std::unique_ptr<Mesh> mMesh;
        std::unique_ptr<Material> mMaterial;

        bool mRenderable;

    private:
        void LoadMesh(std::ifstream& pFile);
        void LoadMaterial(std::ifstream& pFile);


        std::string mObjPath;
        std::string mObjName;
    };
}
