#pragma once
#include "Singleton.h"
#include "BaseAsset.h"
#include "GUIDComparer.h"

namespace Spartan::Serialization
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