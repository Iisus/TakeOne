#include "assimp/scene.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void saveObjectToFile(string dest, const vector<unsigned int>& header, const vector<float>& vbo,
        const vector<unsigned int> ibo, const vector<unsigned int>& mtlHeader, const vector<float>& mtlValues)
{
    ofstream file(dest, ios::binary);
    if(!file.is_open())
    {
        cout << "Error writting the file"<<endl;
        file.close();
        return;
    }

    file.write((char*) &header[0], header.size() * sizeof(unsigned int));
    file.write((char*) &vbo[0], vbo.size() * sizeof(float));
    file.write((char*) &ibo[0], ibo.size() * sizeof(unsigned int));

    file.write((char*) &mtlHeader[0], mtlHeader.size() * sizeof(unsigned int));
    file.write((char*) &mtlValues[0], mtlValues.size() * sizeof(float));

    file.close();
}

void loadColor(const aiMaterial* mtl, vector<unsigned int>& header, vector<float>& values, const char* key, unsigned int type, unsigned int index)
{
    aiColor4D color(0.0f, 0.0f, 0.0f, 0.0f);

    header.push_back(AI_SUCCESS == aiGetMaterialColor(mtl, key, type, index, &color));
    values.push_back(color.r);
    values.push_back(color.g);
    values.push_back(color.b);
    values.push_back(color.a);
}

void loadFloat(const aiMaterial* mtl, vector<unsigned int>& header, vector<float>& values, const char* key, unsigned int type, unsigned int index)
{
    float property = 0;
    header.push_back(AI_SUCCESS == aiGetMaterialFloat(mtl, key, type, index, &property));
    values.push_back(property);
}

void loadMaterial(const aiMaterial* mtl, vector<unsigned int>& header, vector<float>& values)
{
    loadColor(mtl, header, values, AI_MATKEY_COLOR_AMBIENT);
    loadColor(mtl, header, values, AI_MATKEY_COLOR_DIFFUSE);
    loadColor(mtl, header, values, AI_MATKEY_COLOR_EMISSIVE);
    loadColor(mtl, header, values, AI_MATKEY_COLOR_REFLECTIVE);
    loadColor(mtl, header, values, AI_MATKEY_COLOR_SPECULAR);
    loadColor(mtl, header, values, AI_MATKEY_COLOR_TRANSPARENT);

    loadFloat(mtl, header, values, AI_MATKEY_OPACITY);
    loadFloat(mtl, header, values, AI_MATKEY_REFLECTIVITY);
    loadFloat(mtl, header, values, AI_MATKEY_REFRACTI);
    loadFloat(mtl, header, values, AI_MATKEY_SHININESS);
    loadFloat(mtl, header, values, AI_MATKEY_SHININESS_STRENGTH);
}

void loadScene(const aiScene* scene, const aiNode* node, string destPath)
{
    for(int i=0; i < node->mNumMeshes; i++)
    {
        string destFile = destPath + node->mName.C_Str() + ".t1o";

        const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        vector<unsigned int> mtlHeader;
        vector<float> mtlValues;

        loadMaterial(scene->mMaterials[mesh->mMaterialIndex], mtlHeader, mtlValues);

        //header:pnct v_size i_size
        vector<unsigned int> header;
        vector<float> vbo;
        vector<unsigned int> ibo;

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

        saveObjectToFile(destFile, header, vbo, ibo, mtlHeader, mtlValues);
    }

    for(int n = 0; n < node->mNumChildren; ++n)
    {
        loadScene(scene, node->mChildren[n], destPath);
    }
}

int main(int argc, char *argv[])
{
    const char* source = argv[1];
    string dest = argc>2 ? argv[2] : "";

    cout<<dest<<endl;

    const aiScene* scene;
    if(argc < 2)
    {
        cout<<"You need to provide the source"<<endl;
        return 0;
    }
    if(! (scene = aiImportFile(source,aiProcessPreset_TargetRealtime_MaxQuality)) )
    {
        cout<<"Cannot load file " << source << endl;
        return 0;
    }

    loadScene(scene, scene->mRootNode, dest);

    cout<<"Success!"<<endl;
    return 0;
}