#pragma once
#include "SerializedObject.h"
#include "BaseAsset.h"

namespace Spartan::Serialization
{
	template<class T>
	class ScriptableObject : public BaseAsset
	{
	public:
		ScriptableObject() : BaseAsset() {}
		virtual ~ScriptableObject() {}

		BASIC_OBJECT(T, BaseAsset);
	};
}