#pragma once
#include "SEObject.h"

namespace Spartan
{
	struct SerializedProperty
	{
	public:
		SerializedProperty(std::any data, void* member);

		std::any m_Serialized;
		void* m_MemberPointer;
	};

	class BaseAsset : public Spartan::SEObject
	{
	public:
		BaseAsset(const GUID& guid);
		virtual ~BaseAsset() {}

		virtual const std::type_info& GetClassType() = 0;

		void Serialize(std::ofstream& os);
		void Deserialize(std::ifstream& os);

		const GUID& GetGUID();

	protected:
		virtual void DefineSerializedProperties(std::vector<SerializedProperty>& params) = 0;
		virtual BaseAsset* Create(const GUID& guid) = 0;

	private:
		void PrepareData();
		void Serialize(SerializedProperty& data, std::ofstream& fileStream);
		void Deserialize(SerializedProperty& data, std::ifstream& fileStream);

	private:
		friend class AssetManager;
		friend class AssetDatabase;
		const GUID m_GUID;
		std::vector<SerializedProperty> m_SerializedData;
	};

	template<class T>
	class Asset : public BaseAsset
	{
	public:
		Asset(const GUID& guid) : BaseAsset(guid) {}
		virtual ~Asset() {}

		virtual const std::type_info& GetClassType() override
		{
			return typeid(T);
		}

	private:
		virtual BaseAsset* Create(const GUID& guid) override
		{
			return new T(guid);
		}
	};
}