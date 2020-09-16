#include "stdafx.h"
#include "AssetManager.h"
#include "AssetDatabase.h"

namespace Spartan
{
	Content* AssetManager::CreateInstance(const std::type_info& type)
	{
		return (Content*)SEObject::CreateObject(type);
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
}
