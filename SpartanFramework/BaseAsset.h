#pragma once
#include "SerializedObject.h"

namespace Spartan::Serialization
{
	class BaseAsset : public SerializedObject
	{
	public:
		BaseAsset(const GUID& guid);
		virtual ~BaseAsset() {}

		virtual const std::type_info& GetClassType() = 0;

		const GUID& GetGUID();

		virtual BaseAsset* Create(const GUID& guid) = 0;

	private:
		virtual void PrepareData(std::vector<SerializedProperty>& props) override;

	private:
		friend class AssetManager;
		friend class AssetDatabase;
		const GUID m_GUID;
	};
}