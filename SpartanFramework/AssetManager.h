#pragma once
#include "BaseAsset.h"
#include "Singleton.h"
#include "GUIDComparer.h"
#include "Content.h"

namespace Spartan
{
	class AssetManager : public Singleton<AssetManager>
	{
	public:
		AssetManager() {}
		virtual ~AssetManager() {}

		template<class T>
		static T* CreateInstance()
		{
			const std::type_info& type = typeid(T);
			return (T*)SEObject::CreateObject<T>();
		}

		static Content* CreateInstance(const std::type_info& type);

		static Content* GetAsset(GUID guid);

	private:
		static void AddAsset(Content* asset);

	private:
		friend class BaseAsset;
		friend class AssetDatabase;
		friend class ScriptableObjectLoader;

	private:
		std::map<GUID, Content*, Serialization::GUIDComparer> m_Assets;
	};
}