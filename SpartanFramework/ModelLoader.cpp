#include "stdafx.h"
#include "ModelLoader.h"
#include <filesystem>

namespace Spartan
{
    ModelLoader::ModelLoader()
    {
    }

    ModelLoader::~ModelLoader()
    {
    }

    Model* ModelLoader::LoadContent(const std::string& file)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
            return nullptr;
        }
        //directory = file.substr(0, file.find_last_of('/'));

        Model* pModel = new Model();
        ProcessNode(scene->mRootNode, scene, pModel);
        return pModel;
    }

    void ModelLoader::ProcessNode(aiNode* node, const aiScene* scene, Model* pModel)
    {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            pModel->AddMesh(ProcessMesh(mesh));
        }
        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene, pModel);
        }
    }

    Mesh* ModelLoader::ProcessMesh(aiMesh* mesh)
    {
        float* vertices = nullptr;
        vector<MeshAttribute> attributes;
        vector<unsigned int> indices;
        size_t vertexSize = 0;
        //vector<Texture> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            if (i == 0)
            {
                attributes.push_back(MeshAttribute::APosition3D);
                attributes.push_back(MeshAttribute::ANormal);
                vertexSize = 24;

                //vertexSize += sizeof(Vector3) * 2;
            }

            std::vector<float> vertexData;
            // process vertex positions, normals and texture coordinates
            vertexData.push_back(mesh->mVertices[i].x);
            vertexData.push_back(mesh->mVertices[i].y);
            vertexData.push_back(mesh->mVertices[i].z);
            vertexData.push_back(mesh->mNormals[i].x);
            vertexData.push_back(mesh->mNormals[i].y);
            vertexData.push_back(mesh->mNormals[i].z);

            //if (mesh->mTextureCoords[0])
            //{
            //    vertexData.push_back(mesh->mTextureCoords[0][i].x);
            //    vertexData.push_back(mesh->mTextureCoords[0][i].y);

            //    if (i == 0)
            //    {
            //        attributes.push_back(MeshAttribute::ACoord);
            //        vertexSize += sizeof(Vector2);
            //    }
            //}

            //if (mesh->HasTangentsAndBitangents())
            //{
            //    vertexData.push_back(mesh->mTangents[i].x);
            //    vertexData.push_back(mesh->mTangents[i].y);
            //    vertexData.push_back(mesh->mTangents[i].z);
            //    vertexData.push_back(mesh->mBitangents[i].x);
            //    vertexData.push_back(mesh->mBitangents[i].y);
            //    vertexData.push_back(mesh->mBitangents[i].z);

            //    if (i == 0)
            //    {
            //        attributes.push_back(MeshAttribute::ATangent);
            //        attributes.push_back(MeshAttribute::ABiNormal);

            //        vertexSize += sizeof(Vector3) * 2;
            //    }
            //}

            if (i == 0) vertices = new float[mesh->mNumVertices * vertexSize];

            //vertices[i] = RawVertex(vertexData);
            memcpy(&vertices[i * (vertexSize / sizeof(float))], &vertexData[0], vertexSize);
        }

        /*for (size_t i = 0; i < mesh->mNumVertices * vertexSize; i++)
        {
            Utilities::Debug::LogInfo(std::to_string(vertices[i]));
        }*/

        // process indices
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        Mesh* pMesh = new Mesh(mesh->mNumVertices, vertices, indices.size(), indices.data(), vertexSize, attributes.size(), attributes.data(), GL_TRIANGLES);
        pMesh->BuildMesh();
        delete[] vertices;
        return pMesh;
    }
}