#include "stdafx.h"
#include "SerializedObject.h"
#include "Serializer.h"
#include "AssetDatabase.h"
#include "AssetManager.h"

namespace Spartan::Serialization
{
	SerializedObject::SerializedObject() : m_IsDirty(false)
	{
	}

	SerializedObject::~SerializedObject()
	{
	}

	void SerializedObject::CollectProperties()
	{
		m_SerializedData.clear();
		DefineSerializedProperties(m_SerializedData);
	}

	void SerializedObject::Serialize(std::ofstream& os)
	{
		PrepareData();

		std::for_each(m_SerializedData.begin(), m_SerializedData.end(), [&](SerializedProperty& data)
			{
				Serialize(data, os);
			});
	}

	void SerializedObject::Deserialize(std::ifstream& os, int skipCount)
	{
		PrepareData();

		int index = 0;
		std::for_each(m_SerializedData.begin(), m_SerializedData.end(), [&](SerializedProperty& data)
			{
				if (index >= skipCount) Deserialize(data, os);
				++index;
			});
	}

	SerializedProperty& SerializedObject::GetSerializedProperty(int index)
	{
		return m_SerializedData[index];
	}

	size_t SerializedObject::GetSerializedPropertyCount() const
	{
		return m_SerializedData.size();
	}

	void SerializedObject::PrepareData()
	{
		m_SerializedData.clear();
		const std::type_info& type = GetType();
		size_t hashCode = Spartan::SEObject::GetClassHash(type);
		m_SerializedData.push_back(SerializedProperty(hashCode, NULL, "HASHCODE"));
		m_SerializedData.push_back(SerializedProperty(m_GUID, &m_GUID, "GUID"));
		PrepareData(m_SerializedData);
		DefineSerializedProperties(m_SerializedData);
	}

	void SerializedObject::Serialize(SerializedProperty& data, std::ofstream& fileStream)
	{
		Serializer::Serialize(data, fileStream);
	}

	void SerializedObject::Deserialize(SerializedProperty& data, std::ifstream& fileStream)
	{
		Serializer::Deserialize(data, fileStream);
	}
}