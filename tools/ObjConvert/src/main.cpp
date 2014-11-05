#include "assimp/scene.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include <iostream>
#include <fstream>

using namespace std;

void saveToFile(const std::vector<unsigned int>& header, const std::vector<float>& vbo, const std::vector<unsigned int> ibo)
{
    ofstream file("teapot.t1o", ios::binary);
    if(!file.is_open())
    {
        cout << "Error writting the file"<<endl;
        file.close();
        return;
    }

    file.write((char*) &header[0], header.size() * sizeof(unsigned int));
    file.write((char*) &vbo[0], vbo.size() * sizeof(float));
    file.write((char*) &ibo[0], ibo.size() * sizeof(unsigned int));

    file.close();
}

void loadScene(const aiScene* scene, const aiNode* node)
{
    for(int i=0; i < node->mNumMeshes; i++)
    {
        const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        //header:pnct v_size i_size
        std::vector<unsigned int> header;
        std::vector<float> vbo;
        std::vector<unsigned int> ibo;

        bool hasPos = mesh->HasPositions();
        bool hasNor = mesh->HasNormals();
        bool hasCol = mesh->HasVertexColors(0);
        bool hasTex = mesh->HasTextureCoords(0);

        //setup vertex format
        header.push_back(static_cast<unsigned int>(hasPos));
        header.push_back(static_cast<unsigned int>(hasNor));
        header.push_back(static_cast<unsigned int>(hasCol));
        header.push_back(static_cast<unsigned int>(hasTex));

        //setup vbo
        for(int j = 0; j < mesh->mNumVertices; j++)
        {
            //insert positions
            vbo.push_back(hasPos ? mesh->mVertices[j].x : 0);
            vbo.push_back(hasPos ? mesh->mVertices[j].y : 0);
            vbo.push_back(hasPos ? mesh->mVertices[j].z : 0);

            //insert normals
            vbo.push_back(hasNor ? mesh->mNormals[j].x : 0);
            vbo.push_back(hasNor ? mesh->mNormals[j].y : 0);
            vbo.push_back(hasNor ? mesh->mNormals[j].z : 0);

            //insert colors
            vbo.push_back(hasCol ? mesh->mColors[0][j].r : 0);
            vbo.push_back(hasCol ? mesh->mColors[0][j].g : 0);
            vbo.push_back(hasCol ? mesh->mColors[0][j].b : 0);

            //insert texture coordinates
            vbo.push_back(hasTex ? mesh->mTextureCoords[0][j].x : 0);
            vbo.push_back(hasTex ? mesh->mTextureCoords[0][j].y : 0);
        }

        //setup ibo
        for(int j = 0; j < mesh->mNumFaces; j++)
        {
            ibo.push_back(mesh->mFaces[j].mIndices[0]);
            ibo.push_back(mesh->mFaces[j].mIndices[1]);
            ibo.push_back(mesh->mFaces[j].mIndices[2]);
        }

        //setup vertex and index count
        header.push_back(mesh->mNumVertices);
        header.push_back(ibo.size());

        saveToFile(header, vbo, ibo);
    }

    for(int n = 0; n < node->mNumChildren; ++n)
    {
        loadScene(scene, node->mChildren[n]);
    }
}

int main()
{
    const char* path = "teapot.obj";
    const aiScene* scene = aiImportFile(path,aiProcessPreset_TargetRealtime_MaxQuality);

    loadScene(scene, scene->mRootNode);

    return 0;
}