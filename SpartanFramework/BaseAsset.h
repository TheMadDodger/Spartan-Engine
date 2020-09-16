#pragma once
#include "SerializedObject.h"

namespace Spartan::Serialization
{
	class BaseAsset : public SerializedObject
	{
	public:
		BaseAsset();
		virtual ~BaseAsset() {}
		virtual SEObject* Create() = 0;

	private:
		virtual void PrepareData(std::vector<SerializedProperty>& props) override;

	private:
		friend class AssetManager;
		friend class AssetDatabase;
		friend class ScriptableObjectLoader;
	};
}