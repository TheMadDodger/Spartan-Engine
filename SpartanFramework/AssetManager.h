#pragma once
#include "Asset.h"
#include "Singleton.h"
#include "GUIDComparer.h"

namespace SpartanEngine
{
	class AssetManager : public Singleton<AssetManager>
	{
	public:
		AssetManager() {}
		virtual ~AssetManager() {}

		template<class T>
		static void RegisterAsset()
		{
			AssetManager* pInstance = GetInstance();

			const std::type_info& type = typeid(T);
			size_t hashCode = GetAssetHash<T>();
			auto it = pInstance->m_AssetTemplates.find(hashCode);
			if (it != pInstance->m_AssetTemplates.end()) return;
			pInstance->m_AssetTemplates[hashCode] = new T(GUID());
		}

		template<class T>
		static size_t GetAssetHash()
		{
			const std::type_info& type = typeid(T);
			return GetAssetHash(type);
		}

		static size_t GetAssetHash(const std::type_info& type);

		template<class T>
		static T* CreateInstance()
		{
			const std::type_info& type = typeid(T);
			return (T*)CreateInstance(type);
		}

		static BaseAsset* CreateInstance(const std::type_info& type);

	private:
		static void AddAsset(BaseAsset* asset);
		static BaseAsset* GetAsset(GUID guid);
		static BaseAsset* GetAssetTemplate(size_t assetHash);

	private:
		friend class BaseAsset;
		friend class AssetDatabase;

	private:
		std::map<size_t, BaseAsset*> m_AssetTemplates;
		std::map<GUID, BaseAsset*, GUIDComparer> m_Assets;
		
		static std::hash<std::string> m_AssetHasher;
	};
}