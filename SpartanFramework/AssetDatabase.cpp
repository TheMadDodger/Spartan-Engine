#include "stdafx.h"
#include "AssetDatabase.h"
#include "AssetManager.h"

namespace Spartan
{
	AssetDatabase::AssetDatabase()
	{
	}

	AssetDatabase::~AssetDatabase()
	{
	}

	BaseAsset* AssetDatabase::LoadAsset(GUID guid)
	{
		BaseAsset* pAsset = AssetManager::GetAsset(guid);
		if (pAsset != nullptr) return pAsset;

		AssetDatabase* pInstance = GetInstance();
		auto it = pInstance->m_AssetPaths.find(guid);
		if (it == pInstance->m_AssetPaths.end()) return nullptr;
		std::string path = pInstance->m_AssetPaths[guid];
		return LoadAsset(path);
	}

	BaseAsset* AssetDatabase::LoadAsset(const std::string& relativeAssetPath)
	{
		std::ifstream fileStream("./Resources/Assets/" + relativeAssetPath);
		BaseAsset* pAsset = DeserializeToAsset(fileStream);
		fileStream.close();
		return pAsset;
	}

	BaseAsset* AssetDatabase::DeserializeToAsset(std::ifstream& fileStream)
	{
		size_t assetHash;
		GUID assetGUID;
		fileStream.read((char*)&assetHash, sizeof(size_t));
		fileStream.read((char*)&assetGUID, sizeof(GUID));
		BaseAsset* assetTemplate = AssetManager::GetAssetTemplate(assetHash);
		if (assetTemplate == nullptr) return nullptr;

		// TODO: Check if the GUID already exists
		BaseAsset* deserializedAsset = assetTemplate->Create(assetGUID);
		deserializedAsset->Deserialize(fileStream);
		return deserializedAsset;
	}
}