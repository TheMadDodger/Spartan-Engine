#include "stdafx.h"
#include "Serializer.h"

#define REGISTER_DEFAULT_SERIALIZER(type) m_Serializers.push_back(new TypeSerializer<type>());

namespace SpartanEngine
{
	std::vector<BaseSerializer*> Serializer::m_Serializers;

	void Serializer::LoadSerializers()
	{
		m_Serializers.clear();
		REGISTER_DEFAULT_SERIALIZER(GUID);
		REGISTER_DEFAULT_SERIALIZER(size_t);
		REGISTER_DEFAULT_SERIALIZER(float);
		REGISTER_DEFAULT_SERIALIZER(int);
		REGISTER_DEFAULT_SERIALIZER(unsigned int);
		REGISTER_DEFAULT_SERIALIZER(double);
		REGISTER_DEFAULT_SERIALIZER(bool);
		REGISTER_DEFAULT_SERIALIZER(long);
		REGISTER_DEFAULT_SERIALIZER(unsigned long);
		REGISTER_DEFAULT_SERIALIZER(short);
		REGISTER_DEFAULT_SERIALIZER(unsigned short);
		REGISTER_DEFAULT_SERIALIZER(char);
		REGISTER_DEFAULT_SERIALIZER(unsigned char);
	}

	BaseSerializer* Serializer::GetSerializer(const std::type_info& type)
	{
		auto it = std::find_if(m_Serializers.begin(), m_Serializers.end(), [&](BaseSerializer* serializer)
		{
			return serializer->GetSerializedType() == type;
		});

		if (it == m_Serializers.end()) return nullptr;
		BaseSerializer* serializer = *it;
		return serializer;
	}
}