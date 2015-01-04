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
        RenderObject();
        RenderObject(const std::string& pObjPath);

        void Load(const std::string& pObjPath);
        void Render();

        inline Mesh& GetMesh() { return *mMesh; }
        inline Material& GetMaterial() { return *mMaterial; }

        std::string mObjPath;
    private:
        void LoadMesh(std::ifstream& pFile);
        void LoadMaterial(std::ifstream& pFile);

        std::unique_ptr<Mesh> mMesh;
        std::unique_ptr<Material> mMaterial;
    };
}
