#include "stdafx.h"
#include "Serializer.h"

#define REGISTER_DEFAULT_SERIALIZER(type) m_Serializers.push_back(new TypeSerializer<type>());

namespace Spartan::Serialization
{
	std::vector<BaseSerializer*> Serializer::m_Serializers;
	//AssetReferenseSerializer* Serializer::m_pAssetReferenceSerializer = nullptr;

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

		//m_pAssetReferenceSerializer = new AssetReferenseSerializer();
	}

	void Serializer::Destroy()
	{
		std::for_each(m_Serializers.begin(), m_Serializers.end(), [&](BaseSerializer* pSerializer)
		{
			delete pSerializer;
		});

		m_Serializers.clear();
		//delete m_pAssetReferenceSerializer;
		//m_pAssetReferenceSerializer = nullptr;
	}

	void Serializer::Serialize(SerializedProperty& data, std::ofstream& fileStream)
	{
		if (data.m_IsContainer)
		{
			SerializeContainer(data, fileStream);
			return;
		}

		if (data.m_pAssetReference)
		{
			SerializeAssetReference(data, fileStream);
			return;
		}

		BaseSerializer* serializer = GetSerializer(data.m_Serialized.type());
		if (serializer == nullptr) return;
		serializer->Serialize(data.m_Serialized, fileStream);
	}

	void Serializer::Deserialize(SerializedProperty& data, std::ifstream& fileStream)
	{
		if (data.m_pAssetReference)
		{
			DeserializeAssetReference(data, fileStream);
			return;
		}

		BaseSerializer* serializer = Serializer::GetSerializer(data.m_Serialized.type());
		if (serializer == nullptr) return;
		serializer->Deserialize(data.m_Serialized, data.m_MemberPointer, fileStream);
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

	//AssetReferenseSerializer* Serializer::GetAssetReferenseSerializer()
	//{
	//	return m_pAssetReferenceSerializer;
	//}

	void Serializer::SerializeAssetReference(SerializedProperty& prop, std::ofstream& fileStream)
	{
		if (!prop.m_pAssetReference) return;
		fileStream.write((const char*)&prop.m_pAssetReference->GetAssetGUID(), sizeof(GUID));
	}

	void Serializer::DeserializeAssetReference(SerializedProperty& prop, std::ifstream& fileStream)
	{
		GUID assetGUID;
		fileStream.read((char*)&assetGUID, sizeof(GUID));
		prop.m_pAssetReference->SetAsset(assetGUID);
	}

	void Serializer::SerializeContainer(SerializedProperty& data, std::ofstream& fileStream)
	{

	}
}