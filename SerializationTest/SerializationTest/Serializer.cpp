#include "Serializer.h"

std::map<const std::type_info&, BaseSerializer> Serializer::m_Serializers = std::map<const std::type_info&, BaseSerializer>();

void Serializer::LoadSerializers()
{
	m_Serializers.clear();
	m_Serializers[typeid(float)] =				TypeSerializer<float>();
	m_Serializers[typeid(int)] =				TypeSerializer<int>();
	m_Serializers[typeid(unsigned int)] =		TypeSerializer<unsigned int>();
	m_Serializers[typeid(double)] =				TypeSerializer<double>();
	m_Serializers[typeid(size_t)] =				TypeSerializer<size_t>();
	m_Serializers[typeid(bool)] =				TypeSerializer<bool>();
	m_Serializers[typeid(long)] =				TypeSerializer<long>();
	m_Serializers[typeid(unsigned long)] =		TypeSerializer<unsigned long>();
	m_Serializers[typeid(long)] =				TypeSerializer<short>();
	m_Serializers[typeid(unsigned long)] =		TypeSerializer<unsigned short>();
	m_Serializers[typeid(char)] =				TypeSerializer<char>();
	m_Serializers[typeid(unsigned char)] =		TypeSerializer<unsigned char>();
	m_Serializers[typeid(GUID)] =				GUIDSerializer();
}

BaseSerializer* Serializer::GetSerializer(const std::type_info& type)
{
	auto it = m_Serializers.find(type);
	if (it == m_Serializers.end()) return nullptr;
	return &m_Serializers[type];
}
