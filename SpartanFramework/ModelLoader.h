#pragma once
#include "ContentLoader.h"
#include "Mesh.h"

#pragma region Extension Loaders
class ExtensionMeshLoader
{
public:
	ExtensionMeshLoader(const std::string &extension);
	~ExtensionMeshLoader();

	virtual void Initialize() = 0;

	virtual MeshData* LoadMesh(const std::string& file) = 0;

	const std::string& GetExtension() const;

private:
	const std::string m_Extension;
};

class FBXMeshLoader : public ExtensionMeshLoader
{
public:
	FBXMeshLoader();
	~FBXMeshLoader();

	virtual MeshData* LoadMesh(const std::string& file) override;
	virtual void Initialize() override;

private:
	fbxsdk::FbxManager* m_pFBXManager;
	int m_NumTabs = 0;

private:
	void PrintTabs();
	void PrintNode(FbxNode* pNode);
	void PrintAttribute(FbxNodeAttribute* pAttribute);
	FbxString GetAttributeTypeName(FbxNodeAttribute::EType type);
};
#pragma endregion

class ModelLoader : public ContentLoader<Mesh>
{
public:
	ModelLoader();
	~ModelLoader();

	Mesh* LoadContent(const std::string& file) override;

private:
	std::map<std::string, ExtensionMeshLoader*> m_ExtensionLoaders;
};
