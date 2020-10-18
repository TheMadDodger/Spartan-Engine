#pragma once
#include "Singleton.h"
#include "BaseAsset.h"
#include "GUIDComparer.h"
#include "LocalDatabase.h"
#include "MetaData.h"
#include "Event.h"

namespace Spartan
{
	class AssetDatabase : public Singleton<AssetDatabase>
	{
	public:
		AssetDatabase();
		virtual ~AssetDatabase();

		static void Save();
		static void Refresh();

		static void DiscoverAssets();
		static std::string GetAssetPath(Content* pAsset);

		static void CreateAsset(Content* pAsset, const std::string& path);

		static void SaveAssets();

		static void GetAllAssetsOfType(const std::type_info& type, std::vector<Content*>& pAssets);

	private:
		void WriteDatabase();

		static void ProcessDirectory(const std::string& path);
		static void ProcessFile(const std::filesystem::path& filePath);

		size_t GetTypeID(const std::type_info& type);
		bool AddType(const std::type_info& type);

		std::string GetAssetPath(const GUID& guid);
		GUID AddAsset(const std::type_info& assetType, const std::string& name, const std::string& path);

		GUID StringToGuid(const std::string& str);
		std::string GuidToString(GUID guid);

		std::string GetAssetPath_Internal(Content* pAsset);
		void CreateAsset_Internal(Content* pAsset, const std::string& path);

		void Save(Content* pAsset);

		void GetAllAssetsOfType_Internal(const std::type_info& type, std::vector<Content*>& pAssets);

	private:
		friend class AssetManager;
		LocalDatabase* m_pDatabaseInstance;
	};
}