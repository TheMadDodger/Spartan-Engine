#include "SerializableAsset.h"
#include <vector>
#include <xlocale>
#include <sstream>
#include <algorithm>
#include "Serializer.h"

void SerializedAsset::Serialize(std::ostream& os)
{
	PrepareData();

	std::for_each(m_SerializedData.begin(), m_SerializedData.end(), [&](std::any& data)
	{
		os << Serialize(data);
	});
}

const GUID& SerializedAsset::GetGUID()
{
	return m_GUID;
}

void SerializedAsset::PrepareData()
{
	m_SerializedData.clear();
	size_t hashCode = GetClassType().hash_code();
	m_SerializedData.push_back(hashCode);
	m_SerializedData.push_back(m_GUID);
	DefineSerializedParams(m_SerializedData);
}

std::string SerializedAsset::Serialize(std::any& data)
{
	BaseSerializer *serializer = Serializer::GetSerializer(data.type());
	if (serializer == nullptr) return "";
	return serializer->Serialize(data);
}

void TestAsset::Deserialize(std::istream& is)
{
	GUID guid;
	is >> guid.Data4;
	is >> guid.Data3;
	is >> guid.Data2;
	is >> guid.Data1;
	size_t hashCode;
	is >> hashCode;
}

void TestAsset::DefineSerializedParams(std::vector<std::any>& params)
{
	params.push_back(m_TestData1);
	params.push_back(m_TestData2);
	params.push_back(m_TestData3);
	params.push_back(m_TestData4);
}
