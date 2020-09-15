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

		//static Serialization::BaseAsset* LoadAsset(const std::string& relativeAssetPath);
		static Content* LoadAsset(GUID guid);

		static void Save();
		static void Refresh();

		static void DiscoverAssets();

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

	private:
		friend class AssetManager;
		//map<GUID, std::string, Serialization::GUIDComparer> m_AssetPaths;
		LocalDatabase* m_pDatabaseInstance;
	};
}