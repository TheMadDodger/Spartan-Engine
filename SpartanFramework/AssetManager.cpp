#include "stdafx.h"
#include "AssetManager.h"

namespace SpartanEngine
{
	std::hash<std::string> AssetManager::m_AssetHasher;

	size_t AssetManager::GetAssetHash(const std::type_info& type)
	{
		std::string name = type.name();
		return m_AssetHasher(name);
	}

	BaseAsset* AssetManager::CreateInstance(const std::type_info& type)
	{
		AssetManager* pInstance = GetInstance();

		size_t assetHash = GetAssetHash(type);
		GUID newGUID;
		if (CoCreateGuid(&newGUID) != S_OK) return nullptr;
		return pInstance->m_AssetTemplates[assetHash]->Create(newGUID);
	}

	BaseAsset* AssetManager::GetAsset(GUID guid)
	{
		AssetManager* pInstance = GetInstance();
		auto it = pInstance->m_Assets.find(guid);
		if (it == pInstance->m_Assets.end()) return nullptr;
		return pInstance->m_Assets[guid];
	}

	void AssetManager::AddAsset(BaseAsset* asset)
	{
		GetInstance()->m_Assets[asset->m_GUID] = asset;
	}

	BaseAsset* AssetManager::GetAssetTemplate(size_t assetHash)
	{
		AssetManager* pInstance = GetInstance();
		auto it = pInstance->m_AssetTemplates.find(assetHash);
		if (it == pInstance->m_AssetTemplates.end()) return nullptr;
		return pInstance->m_AssetTemplates[assetHash];
	}
}
