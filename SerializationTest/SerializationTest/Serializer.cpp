#include "stdafx.h"
#include "Serializer.h"

std::vector<BaseSerializer*> Serializer::m_Serializers;

void Serializer::LoadSerializers()
{
	m_Serializers.clear();
	m_Serializers.push_back(new	TypeSerializer<GUID>());
	m_Serializers.push_back(new	TypeSerializer<size_t>());
	m_Serializers.push_back(new	TypeSerializer<float>());
	m_Serializers.push_back(new	TypeSerializer<int>());
	m_Serializers.push_back(new	TypeSerializer<unsigned int>());
	m_Serializers.push_back(new	TypeSerializer<double>());
	m_Serializers.push_back(new	TypeSerializer<bool>());
	m_Serializers.push_back(new	TypeSerializer<long>());
	m_Serializers.push_back(new	TypeSerializer<unsigned long>());
	m_Serializers.push_back(new	TypeSerializer<short>());
	m_Serializers.push_back(new	TypeSerializer<unsigned short>());
	m_Serializers.push_back(new	TypeSerializer<char>());
	m_Serializers.push_back(new	TypeSerializer<unsigned char>());
}

BaseSerializer* Serializer::GetSerializer(const std::type_info& type)
{
	auto it = std::find_if(m_Serializers.begin(), m_Serializers.end(), [&](BaseSerializer *serializer)
	{
		return serializer->GetSerializedType() == type;
	});

	if (it == m_Serializers.end()) return nullptr;
	BaseSerializer* serializer = *it;
	return serializer;
}
