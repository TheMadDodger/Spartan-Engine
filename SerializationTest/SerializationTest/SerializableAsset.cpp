#include "stdafx.h"
#include "SerializableAsset.h"
#include "Serializer.h"
#include "AssetFactory.h"

SerializedAsset::SerializedAsset(const GUID& guid) : m_GUID(guid)
{
	AssetFactory::AddAsset(this);
}

void SerializedAsset::Serialize(std::ofstream& os)
{
	PrepareData();

	std::for_each(m_SerializedData.begin(), m_SerializedData.end(), [&](SerializedParam& data)
	{
		Serialize(data, os);
	});
}

void SerializedAsset::Deserialize(std::ifstream& os)
{
	PrepareData();

	int index = 0;
	std::for_each(m_SerializedData.begin(), m_SerializedData.end(), [&](SerializedParam& data)
	{
		if (index > 1) Deserialize(data, os); // First 2 pieces of data are class hash and GUID these are already deserialized
		++index;
	});
}

const GUID& SerializedAsset::GetGUID()
{
	return m_GUID;
}

void SerializedAsset::PrepareData()
{
	m_SerializedData.clear();
	size_t hashCode = AssetFactory::GetAssetHash(GetClassType());

	SerializedParam param;
	param.m_MemberPointer = NULL;
	param.m_Serialized = hashCode;
	m_SerializedData.push_back(param);
	param.m_MemberPointer = NULL;
	param.m_Serialized = m_GUID;
	m_SerializedData.push_back(param);
	DefineSerializedParams(m_SerializedData);
}

void SerializedAsset::Serialize(SerializedParam& data, std::ofstream& fileStream)
{
	BaseSerializer *serializer = Serializer::GetSerializer(data.m_Serialized.type());
	if (serializer == nullptr) return;
	serializer->Serialize(data.m_Serialized, fileStream);
}

void SerializedAsset::Deserialize(SerializedParam& data, std::ifstream& fileStream)
{
	BaseSerializer* serializer = Serializer::GetSerializer(data.m_Serialized.type());
	if (serializer == nullptr) return;
	serializer->Deserialize(data.m_Serialized, data.m_MemberPointer, fileStream);
}

void TestAsset::DefineSerializedParams(std::vector<SerializedParam>& params)
{
	SerializedParam param;
	param.m_MemberPointer = &m_TestData1;
	param.m_Serialized = m_TestData1;
	params.push_back(param);
	param.m_MemberPointer = &m_TestData2;
	param.m_Serialized = m_TestData2;
	params.push_back(param);
	param.m_MemberPointer = &m_TestData3;
	param.m_Serialized = m_TestData3;
	params.push_back(param);
	param.m_MemberPointer = &m_TestData4;
	param.m_Serialized = m_TestData4;
	params.push_back(param);
}
