#include "assimp/scene.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

string gSource;
string gName;
string gDest;
ofstream gSceneFile;

void saveObjectToFile(string dest, const vector<unsigned int>& header, const vector<float>& vbo,
        const vector<unsigned int> ibo, const vector<unsigned int>& mtlHeader, const vector<float>& mtlValues,
        const string& texPaths)
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
    file.write((char*) texPaths.c_str(), texPaths.size() * sizeof(char));

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

void loadMaterial(const aiMaterial* mtl, vector<unsigned int>& header, vector<float>& values, const string& dest, string& textures)
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

    for(int i = 0; i<mtl->GetTextureCount(aiTextureType_DIFFUSE); i++)
    {
        aiString path;
        mtl->GetTexture(aiTextureType_DIFFUSE, i, &path);
        string pathFormated = path.data;
#ifdef PLATFORM_LINUX
        std::replace( pathFormated.begin(), pathFormated.end(), '\\', '/');
#elif defined(PLATFORM_WIN32)
        std::replace( pathFormated.begin(), pathFormated.end(), '/', '\\');
#endif
        textures += pathFormated;
        if(i < mtl->GetTextureCount(aiTextureType_DIFFUSE) - 1)
        {
            textures += "&";
        }

        //copy the texture in the package
#ifdef PLATFORM_LINUX
        system(("cp \"" + gSource + pathFormated + "\" \"" + dest + "\"").c_str());
#elif defined(PLATFORM_WIN32)
        system(("xcopy \"" + gSource + pathFormated + "\" \"" + dest + "\" /y").c_str());
#endif
    }
    header.push_back(textures.size());
}

void loadScene(const aiScene* scene, const aiNode* node)
{
    static map<string, int> meshNames;
    for(int i=0; i < node->mNumMeshes; i++)
    {
        string name = node->mName.C_Str();
        if(meshNames.find(node->mName.C_Str()) != meshNames.end())
        {
            meshNames[node->mName.C_Str()]++;
            name += to_string(meshNames[node->mName.C_Str()]);
        }
        else
            meshNames[node->mName.C_Str()] = 0;

        string objDest = gDest + name;
#ifdef PLATFORM_LINUX
        system(("mkdir \"" + objDest + "\"").c_str());
#elif defined(PLATFORM_WIN32)
        system(("mkdir \"" + objDest + "\"").c_str());
#endif
        gSceneFile << name << endl;
        string destFile = objDest + "/obj.t1o";

        const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        vector<unsigned int> mtlHeader;
        vector<float> mtlValues;
        string texPaths("");

        loadMaterial(scene->mMaterials[mesh->mMaterialIndex], mtlHeader, mtlValues, objDest, texPaths);

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

        saveObjectToFile(destFile, header, vbo, ibo, mtlHeader, mtlValues, texPaths);
    }

    for(int n = 0; n < node->mNumChildren; ++n)
    {
        loadScene(scene, node->mChildren[n]);
    }
}

int main(int argc, char *argv[])
{
    if(argc<3)
    {
        cout<<"Invalid number of arguments."<<endl;
        return 0;
    }
    gSource = argv[1];
    gName = argv[2];
    gDest = argc>3 ? argv[3] : "";

    cout<<"Source: "<<gSource<<endl
        <<"File Name: "<<gName<<endl
        <<"Destination: "<<gDest<<endl;

    const aiScene* scene;
    if(argc < 2)
    {
        cout<<"You need to provide the source"<<endl;
        return 0;
    }
    if(!(scene = aiImportFile((gSource+gName).c_str(),aiProcessPreset_TargetRealtime_MaxQuality)))
    {
        cout<<"Cannot load file " << "\"" + gSource+gName + "\"" << endl;
        return 0;
    }

    system(("mkdir \"" + gDest + "\"").c_str());

    gSceneFile.open(gDest + "\\scene.txt");

    loadScene(scene, scene->mRootNode);

    cout<<"Success!"<<endl;

    gSceneFile.close();
    return 0;
}