#pragma once
#include "Singleton.h"
#include "BaseAsset.h"
#include "GUIDComparer.h"
#include "LocalDatabase.h"
#include "MetaData.h"

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

	private:
		//static Serialization::BaseAsset* DeserializeToAsset(std::ifstream& fileStream);

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

	private:
		friend class AssetManager;
		//map<GUID, std::string, Serialization::GUIDComparer> m_AssetPaths;
		LocalDatabase* m_pDatabaseInstance;
	};
}