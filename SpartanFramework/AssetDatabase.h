#pragma once
#include "Singleton.h"
#include "BaseAsset.h"
#include "GUIDComparer.h"
#include "LocalDatabase.h"

namespace Spartan::Serialization
{
	class AssetDatabase : public Singleton<AssetDatabase>
	{
	public:
		AssetDatabase();
		virtual ~AssetDatabase();

		static BaseAsset* LoadAsset(const std::string& relativeAssetPath);
		static BaseAsset* LoadAsset(GUID guid);

		static void Save();
		static void Refresh();

	private:
		static BaseAsset* DeserializeToAsset(std::ifstream& fileStream);

		void WriteDatabase();

	private:
		map<GUID, std::string, GUIDComparer> m_AssetPaths;
		LocalDatabase* m_pDatabaseInstance;
	};
}