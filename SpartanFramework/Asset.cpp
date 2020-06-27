#include "stdafx.h"
#include "Asset.h"
#include "Serializer.h"
#include "AssetManager.h"

namespace SpartanEngine
{
	BaseAsset::BaseAsset(const GUID& guid) : m_GUID(guid)
	{
		AssetManager::AddAsset(this);
	}

	void BaseAsset::Serialize(std::ofstream& os)
	{
		PrepareData();

		std::for_each(m_SerializedData.begin(), m_SerializedData.end(), [&](SerializedProperty& data)
		{
			Serialize(data, os);
		});
	}

	void BaseAsset::Deserialize(std::ifstream& os)
	{
		PrepareData();

		int index = 0;
		std::for_each(m_SerializedData.begin(), m_SerializedData.end(), [&](SerializedProperty& data)
		{
			if (index > 1) Deserialize(data, os); // First 2 pieces of data are class hash and GUID these are already deserialized
			++index;
		});
	}

	const GUID& BaseAsset::GetGUID()
	{
		return m_GUID;
	}

	void BaseAsset::PrepareData()
	{
		m_SerializedData.clear();
		size_t hashCode = AssetManager::GetAssetHash(GetClassType());

		m_SerializedData.push_back(SerializedProperty(hashCode, NULL));
		m_SerializedData.push_back(SerializedProperty(m_GUID, NULL));
		DefineSerializedProperties(m_SerializedData);
	}

	void BaseAsset::Serialize(SerializedProperty& data, std::ofstream& fileStream)
	{
		BaseSerializer* serializer = Serializer::GetSerializer(data.m_Serialized.type());
		if (serializer == nullptr) return;
		serializer->Serialize(data.m_Serialized, fileStream);
	}

	void BaseAsset::Deserialize(SerializedProperty& data, std::ifstream& fileStream)
	{
		BaseSerializer* serializer = Serializer::GetSerializer(data.m_Serialized.type());
		if (serializer == nullptr) return;
		serializer->Deserialize(data.m_Serialized, data.m_MemberPointer, fileStream);
	}

	SerializedProperty::SerializedProperty(std::any data, void* member)
	{
		m_Serialized = data;
		m_MemberPointer = member;
	}
}