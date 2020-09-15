#include "stdafx.h"
#include "MetaData.h"
#include "Serializer.h"
#include "AssetManager.h"

namespace Spartan::Serialization
{
	MetaData::MetaData(size_t hashCode, const GUID& guid, const std::string& path) : m_HashCode(hashCode), m_GUID(guid), m_Path(path) {}
	
	void MetaData::Write()
	{
		BaseSerializer* hashCodeSerializer = Serialization::Serializer::GetSerializer(typeid(size_t));
		BaseSerializer* guidSerializer = Serialization::Serializer::GetSerializer(typeid(GUID));

		std::ofstream fStream(m_Path);
		std::any hashCodeAny = m_HashCode;
		std::any guidAny = m_GUID;
		hashCodeSerializer->Serialize(hashCodeAny, fStream);
		guidSerializer->Serialize(guidAny, fStream);
		fStream.close();
	}

	MetaData MetaData::Read(const std::string& path)
	{
		BaseSerializer* hashCodeSerializer = Serialization::Serializer::GetSerializer(typeid(size_t));
		BaseSerializer* guidSerializer = Serialization::Serializer::GetSerializer(typeid(GUID));

		std::ifstream fStream(path);
		std::any hashCodeAny;
		std::any guidAny;

		size_t hashCode;
		GUID guid;
		hashCodeSerializer->Deserialize(hashCodeAny, &hashCode, fStream);
		guidSerializer->Deserialize(guidAny, &guid, fStream);
		fStream.close();

		return MetaData(hashCode, guid, path);
	}
}