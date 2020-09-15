#include "stdafx.h"
#include "AssetManager.h"
#include "AssetDatabase.h"

namespace Spartan
{
	std::hash<std::string> AssetManager::m_AssetHasher;

	size_t AssetManager::GetAssetHash(const std::type_info& type)
	{
		std::string name = type.name();
		return m_AssetHasher(name);
	}

	Content* AssetManager::CreateInstance(const std::type_info& type)
	{
		AssetManager* pInstance = GetInstance();

		size_t assetHash = GetAssetHash(type);
		GUID newGUID;
		if (CoCreateGuid(&newGUID) != S_OK) return nullptr;
		return nullptr;//pInstance->m_AssetTemplates[assetHash]->Create();
	}

	Content* AssetManager::GetAsset(GUID guid)
	{
		AssetManager* pInstance = GetInstance();
		auto it = pInstance->m_Assets.find(guid);
		if (it == pInstance->m_Assets.end())
		{
			std::string path = AssetDatabase::GetInstance()->GetAssetPath(guid);
			Content* pAsset = ContentManager::GetInstance()->Load(BaseGame::GetAssetRootPath() + path);
			if (!pAsset) return nullptr;
			pInstance->m_Assets[guid] = pAsset;
			return pAsset;
		}
		return pInstance->m_Assets[guid];
	}

	void AssetManager::AddAsset(Content* asset)
	{
		GetInstance()->m_Assets[asset->GetGUID()] = asset;
	}

	Content* AssetManager::GetAssetTemplate(size_t assetHash)
	{
		AssetManager* pInstance = GetInstance();
		auto it = pInstance->m_AssetTemplates.find(assetHash);
		if (it == pInstance->m_AssetTemplates.end()) return nullptr;
		return pInstance->m_AssetTemplates[assetHash];
	}
}
