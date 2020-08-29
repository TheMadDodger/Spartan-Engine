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

		BASIC_OBJECT(ScriptableObject, T);

	private:
		virtual BaseAsset* Create(const GUID& guid) override
		{
			return new T(guid);
		}
	};
}