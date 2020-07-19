#pragma once
#include "Singleton.h"
#include "Asset.h"
#include "GUIDComparer.h"

namespace Spartan
{
	class AssetDatabase : public Singleton<AssetDatabase>
	{
	public:
		AssetDatabase();
		virtual ~AssetDatabase();

		static BaseAsset* LoadAsset(const std::string& relativeAssetPath);
		static BaseAsset* LoadAsset(GUID guid);

	private:
		static BaseAsset* DeserializeToAsset(std::ifstream& fileStream);

	private:
		map<GUID, std::string, GUIDComparer> m_AssetPaths;
	};
}