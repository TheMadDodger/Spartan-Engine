#include "stdafx.h"
#include "BaseAsset.h"
#include "AssetManager.h"
#include "AssetDatabase.h"

namespace Spartan::Serialization
{
	BaseAsset::BaseAsset(const GUID& guid) : m_GUID(guid)
	{
		//AssetManager::AddAsset(this);
	}

	void BaseAsset::PrepareData(std::vector<SerializedProperty>& props)
	{
		props.push_back(SerializedProperty(m_GUID, NULL, "GUID"));
	}

	const GUID& BaseAsset::GetGUID() const
	{
		return m_GUID;
	}
}