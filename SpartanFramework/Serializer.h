#pragma once
#include <any>
#include "AssetReference.h"

namespace Spartan::Serialization
{
	struct BaseSerializer
	{
	public:
		virtual const std::type_info& GetSerializedType() const { return typeid(BaseSerializer); }
		virtual void Serialize(std::any& data, std::ofstream& fileStream) const = 0;
		virtual void Deserialize(std::any& data, void* memberPointer, std::ifstream& fileStream) const = 0;
	};

	template<typename T>
	struct TypeSerializer : public BaseSerializer
	{
	public:
		virtual const std::type_info& GetSerializedType() const override
		{
			return typeid(T);
		}

		void Serialize(std::any& data, std::ofstream& fileStream) const override
		{
			return SerializeData(data, fileStream);
		}

		void Deserialize(std::any& data, void* memberPointer, std::ifstream& fileStream) const override
		{
			return DeserializeData(data, memberPointer, fileStream);
		}

	protected:
		// Default serializer
		virtual void SerializeData(std::any& data, std::ofstream& fileStream) const
		{
			T actualData = std::any_cast<T>(data);
			fileStream.write((const char*)&actualData, sizeof(T));
		}

		// Default deserializer
		virtual void DeserializeData(std::any& data, void* memberPointer, std::ifstream& fileStream) const
		{
			T actualData;
			fileStream.read((char*)&actualData, sizeof(T));
			data = actualData;
			if (memberPointer) memcpy(memberPointer, (const void*)&actualData, sizeof(T));
		}
	};

	class Serializer
	{
	public:
		static void LoadSerializers();
		static void Destroy();

		static void Serialize(SerializedProperty& data, std::ofstream& fileStream);
		static void Deserialize(SerializedProperty& data, std::ifstream& fileStream);

		static BaseSerializer* GetSerializer(const std::type_info& type);

	private:
		static void SerializeAssetReference(SerializedProperty& prop, std::ofstream& fileStream);
		static void DeserializeAssetReference(SerializedProperty& prop, std::ifstream& fileStream);

		static void SerializeContainer(SerializedProperty& data, std::ofstream& fileStream);

	private:
		static std::vector<BaseSerializer*> m_Serializers;
	};
}