#include "stdafx.h"
#include "AssetFactory.h"

std::hash<std::string> AssetFactory::m_AssetHasher;
std::map<size_t, SerializedAsset*> AssetFactory::m_AssetTemplates;
std::map<GUID, SerializedAsset*> AssetFactory::m_Assets;

size_t AssetFactory::GetAssetHash(const std::type_info& type)
{
	std::string name = type.name();
	return m_AssetHasher(name);
}

SerializedAsset* AssetFactory::CreateInstance(const std::type_info& type)
{
	size_t assetHash = GetAssetHash(type);
	
	GUID newGUID;
	if (CoCreateGuid(&newGUID) != S_OK) return nullptr;
	return m_AssetTemplates[assetHash]->Create(newGUID);
}

SerializedAsset* AssetFactory::DeserializeToAsset(std::ifstream& fileStream)
{
	size_t assetHash;
	GUID assetGUID;
	fileStream.read((char*)&assetHash, sizeof(size_t));
	fileStream.read((char*)&assetGUID, sizeof(GUID));
	SerializedAsset* assetTemplate = GetAssetTemplate(assetHash);
	if (assetTemplate == nullptr) return nullptr;

	// TODO: Check if the GUID already exists
	SerializedAsset* deserializedAsset = assetTemplate->Create(assetGUID);
	deserializedAsset->Deserialize(fileStream);
	return deserializedAsset;
}

void AssetFactory::AddAsset(SerializedAsset* asset)
{
	//m_Assets[asset->m_GUID] = asset;
}

SerializedAsset* AssetFactory::GetAssetTemplate(size_t assetHash)
{
	auto it = m_AssetTemplates.find(assetHash);
	if (it == m_AssetTemplates.end()) return nullptr;
	return m_AssetTemplates[assetHash];
}
