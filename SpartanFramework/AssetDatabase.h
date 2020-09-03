#pragma once
#include "Singleton.h"
#include "BaseAsset.h"
#include "GUIDComparer.h"
#include "LocalDatabase.h"

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

	private:
		map<GUID, std::string, Serialization::GUIDComparer> m_AssetPaths;
		LocalDatabase* m_pDatabaseInstance;
	};
}