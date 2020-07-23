#pragma once
#include "SerializedObject.h"
#include "BaseAsset.h"

namespace Spartan::Serialization
{
	template<class T>
	class ScriptableObject : public BaseAsset
	{
	public:
		ScriptableObject(const GUID& guid) : BaseAsset(guid) {}
		virtual ~ScriptableObject() {}

		virtual const std::type_info& GetBaseType() override { return typeid(ScriptableObject); }

		virtual const std::type_info& GetType() override
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