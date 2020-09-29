#include "stdafx.h"
#include "AssetReference.h"
#include "AssetManager.h"

namespace Spartan::Serialization
{
	BaseAssetReference::BaseAssetReference() : m_pReferencedAsset(nullptr), m_AssetGUID(GUID()), m_IsDirty(false)
	{
	}

	BaseAssetReference::~BaseAssetReference()
	{
		m_pReferencedAsset = nullptr;
	}

	Content* BaseAssetReference::GetReferencedAsset()
	{
		if (!m_pReferencedAsset) CollectAsset();
		return m_pReferencedAsset;
	}

	void BaseAssetReference::SetAsset(Content* pAsset)
	{
		m_IsDirty = true;
		if (pAsset == nullptr)
		{
			m_AssetGUID = GUID();
			m_pReferencedAsset = nullptr;
			return;
		}

		if (pAsset->GetType() != GetAssetType())
		{
			Utilities::Debug::LogError("Asset type mismatch!");
			return;
		}

		m_AssetGUID = pAsset->GetGUID();
		m_pReferencedAsset = pAsset;
	}

	void BaseAssetReference::SetAsset(const GUID& guid)
	{
		m_AssetGUID = guid;
		m_IsDirty = true;
		CollectAsset();
	}

	const GUID& BaseAssetReference::GetAssetGUID() const
	{
		return m_AssetGUID;
	}

	bool BaseAssetReference::IsDirty()
	{
		bool dirty = m_IsDirty;
		m_IsDirty = false;
		return dirty;
	}

	void BaseAssetReference::CollectAsset()
	{
		m_pReferencedAsset = nullptr;
		Content* pAsset = Spartan::AssetManager::GetAsset(m_AssetGUID);
		if (!pAsset) return;
		if (pAsset->GetType() != GetAssetType())
		{
			Utilities::Debug::LogError("Asset type mismatch!");
			return;
		}
		m_pReferencedAsset = pAsset;
	}
}