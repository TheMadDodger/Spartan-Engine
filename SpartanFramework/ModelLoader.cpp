#include "stdafx.h"
#include "ModelLoader.h"
#include "BinaryContainer.h"
#include <iostream>
#include <filesystem>

#pragma region Extension Loaders
ExtensionMeshLoader::ExtensionMeshLoader(const std::string& extension) : m_Extension(extension) {}
ExtensionMeshLoader::~ExtensionMeshLoader() {}

const std::string& ExtensionMeshLoader::GetExtension() const
{
	return m_Extension;
}

FBXMeshLoader::FBXMeshLoader() : ExtensionMeshLoader("fbx"), m_pFBXManager(nullptr) {}
FBXMeshLoader::~FBXMeshLoader()
{
	m_pFBXManager->Destroy();
}

void FBXMeshLoader::Initialize()
{
	// Create FBX Manager
	m_pFBXManager = fbxsdk::FbxManager::Create();

	// Create IO settings
	FbxIOSettings* ioSettings = FbxIOSettings::Create(m_pFBXManager, IOSROOT);
	m_pFBXManager->SetIOSettings(ioSettings);
}

MeshData* FBXMeshLoader::LoadMesh(const std::string& file)
{
	// Create an importer using the SDK manager.
	FbxImporter* pImporter = FbxImporter::Create(m_pFBXManager, "");

	if (!pImporter->Initialize(file.data(), -1, m_pFBXManager->GetIOSettings()))
	{
		Utilities::Debug::LogError("Call to FbxImporter::Initialize() failed.\nError returned : % s\n\n" + string(pImporter->GetStatus().GetErrorString()));
	}

	string name = file.substr(file.rfind('/'));
	FbxScene* pScene = FbxScene::Create(m_pFBXManager, name.data());
	pImporter->Import(pScene);

	pImporter->Destroy();

	FbxNode* pRootNode = pScene->GetRootNode();
	if (pRootNode) {
		for (int i = 0; i < pRootNode->GetChildCount(); i++)
			PrintNode(pRootNode->GetChild(i));
	}

	return nullptr;

	/*if (!Utilities::BinaryContainer::OpenRead(file.data()))
	{
		Utilities::Debug::LogError("Could not open file for reading!");
	}

	const std::string header = Utilities::BinaryContainer::ReadString();
	char unknownByte1 = Utilities::BinaryContainer::Read<byte>();
	char unknownByte2 = Utilities::BinaryContainer::Read<byte>();
	unsigned int version = Utilities::BinaryContainer::Read<unsigned int>();

	MeshData *meshData = new MeshData(file);
	if (!ReadVersion(version, meshData))
	{
		delete meshData;
		return nullptr;
	}
	return meshData;*/
}

FbxString FBXMeshLoader::GetAttributeTypeName(FbxNodeAttribute::EType type)
{
	switch (type) {
	case FbxNodeAttribute::eUnknown: return "unidentified";
	case FbxNodeAttribute::eNull: return "null";
	case FbxNodeAttribute::eMarker: return "marker";
	case FbxNodeAttribute::eSkeleton: return "skeleton";
	case FbxNodeAttribute::eMesh: return "mesh";
	case FbxNodeAttribute::eNurbs: return "nurbs";
	case FbxNodeAttribute::ePatch: return "patch";
	case FbxNodeAttribute::eCamera: return "camera";
	case FbxNodeAttribute::eCameraStereo: return "stereo";
	case FbxNodeAttribute::eCameraSwitcher: return "camera switcher";
	case FbxNodeAttribute::eLight: return "light";
	case FbxNodeAttribute::eOpticalReference: return "optical reference";
	case FbxNodeAttribute::eOpticalMarker: return "marker";
	case FbxNodeAttribute::eNurbsCurve: return "nurbs curve";
	case FbxNodeAttribute::eTrimNurbsSurface: return "trim nurbs surface";
	case FbxNodeAttribute::eBoundary: return "boundary";
	case FbxNodeAttribute::eNurbsSurface: return "nurbs surface";
	case FbxNodeAttribute::eShape: return "shape";
	case FbxNodeAttribute::eLODGroup: return "lodgroup";
	case FbxNodeAttribute::eSubDiv: return "subdiv";
	default: return "unknown";
	}
}

void FBXMeshLoader::PrintTabs()
{
	for (int i = 0; i < m_NumTabs; i++)
		printf("\t");
}

void FBXMeshLoader::PrintNode(FbxNode* pNode)
{
	PrintTabs();
	const char* nodeName = pNode->GetName();
	FbxDouble3 translation = pNode->LclTranslation.Get();
	FbxDouble3 rotation = pNode->LclRotation.Get();
	FbxDouble3 scaling = pNode->LclScaling.Get();

	// Print the contents of the node.
	printf("<node name='%s' translation='(%f, %f, %f)' rotation='(%f, %f, %f)' scaling='(%f, %f, %f)'>\n",
		nodeName,
		translation[0], translation[1], translation[2],
		rotation[0], rotation[1], rotation[2],
		scaling[0], scaling[1], scaling[2]
	);
	m_NumTabs++;

	// Print the node's attributes.
	for (int i = 0; i < pNode->GetNodeAttributeCount(); i++)
		PrintAttribute(pNode->GetNodeAttributeByIndex(i));

	// Recursively print the children.
	for (int j = 0; j < pNode->GetChildCount(); j++)
		PrintNode(pNode->GetChild(j));

	m_NumTabs--;
	PrintTabs();
	printf("</node>\n");
}

void FBXMeshLoader::PrintAttribute(FbxNodeAttribute* pAttribute)
{
	if (!pAttribute) return;

	FbxString typeName = GetAttributeTypeName(pAttribute->GetAttributeType());
	FbxString attrName = pAttribute->GetName();
	PrintTabs();
	// Note: to retrieve the character array of a FbxString, use its Buffer() method.
	printf("<attribute type='%s' name='%s'/>\n", typeName.Buffer(), attrName.Buffer());
}
#pragma endregion

ModelLoader::ModelLoader()
{
	ExtensionMeshLoader *fbxLoader = new FBXMeshLoader();
	fbxLoader->Initialize();
	m_ExtensionLoaders["fbx"] = fbxLoader;
}

ModelLoader::~ModelLoader()
{
}

Mesh* ModelLoader::LoadContent(const std::string &file)
{
	MeshData * meshData = m_ExtensionLoaders["fbx"]->LoadMesh(file);
	return nullptr;
}
