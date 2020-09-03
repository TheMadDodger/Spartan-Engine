#include "stdafx.h"
#include "AssetDatabase.h"
#include "AssetManager.h"
#include "Serializer.h"

namespace Spartan
{
	AssetDatabase::AssetDatabase() : m_pDatabaseInstance(nullptr) {}

	AssetDatabase::~AssetDatabase()
	{
	}

	Content* AssetDatabase::LoadAsset(GUID guid)
	{
		return nullptr;

		//Content* pAsset = AssetManager::GetAsset(guid);
		//if (pAsset != nullptr) return pAsset;
		//
		//AssetDatabase* pInstance = GetInstance();
		//auto it = pInstance->m_AssetPaths.find(guid);
		//if (it == pInstance->m_AssetPaths.end()) return nullptr;
		//std::string path = pInstance->m_AssetPaths[guid];
		//return LoadAsset(path);
	}

	void AssetDatabase::Save()
	{
		AssetDatabase* pInstance = GetInstance();
		pInstance->WriteDatabase();
	}

	void AssetDatabase::Refresh()
	{

	}

	void AssetDatabase::DiscoverAssets()
	{
		// Scan asset folder
		std::string assetRootFolder = "./../Assets/";
		ProcessDirectory(assetRootFolder);

		// Check for removed files and remove them from the database

		// Save the asset database to file
	}

	//Serialization::BaseAsset* AssetDatabase::LoadAsset(const std::string& relativeAssetPath)
	//{
	//	std::ifstream fileStream("./Resources/Assets/" + relativeAssetPath);
	//	Serialization::BaseAsset* pAsset = DeserializeToAsset(fileStream);
	//	fileStream.close();
	//	return pAsset;
	//}

	//Serialization::BaseAsset* AssetDatabase::DeserializeToAsset(std::ifstream& fileStream)
	//{
	//	size_t assetHash;
	//	GUID assetGUID;
	//	fileStream.read((char*)&assetHash, sizeof(size_t));
	//	fileStream.read((char*)&assetGUID, sizeof(GUID));
	//	Content* assetTemplate = AssetManager::GetAssetTemplate(assetHash);
	//	if (assetTemplate == nullptr) return nullptr;
	//
	//	// TODO: Check if the GUID already exists
	//	Serialization::BaseAsset* deserializedAsset = assetTemplate->Create(assetGUID);
	//	deserializedAsset->Deserialize(fileStream, 2);
	//	return deserializedAsset;
	//}

	void AssetDatabase::WriteDatabase()
	{
		m_pDatabaseInstance = LocalDatabase::BeginDatabase("./Resources/Assets.db");

		for_each(m_AssetPaths.begin(), m_AssetPaths.end(), [&](std::pair<const GUID, std::string>& pair)
		{
			const GUID guid = pair.first;
			std::string path = pair.second;
		});

		LocalDatabase::EndDatabase(m_pDatabaseInstance);
	}

	void AssetDatabase::ProcessDirectory(const std::string& path)
	{
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			if (entry.is_directory())
			{
				ProcessDirectory(entry.path().string());
				continue;
			}
			ProcessFile(entry.path());
		}
	}

	void AssetDatabase::ProcessFile(const std::filesystem::path& filePath)
	{
		auto ext = filePath.extension();
		std::cout << ext << std::endl;
		std::filesystem::path metaExtension = std::filesystem::path(".meta");
		if (ext.compare(metaExtension) == 0) return;
		auto metaFilePath = filePath;
		metaFilePath = metaFilePath.replace_extension(metaExtension);
		if (std::filesystem::exists(metaFilePath))
		{
			// Both file and meta file exists we need to check if it also exists in the database!
			return;
		}

		// Load the file
		Content* pContent = ContentManager::GetInstance()->Load(filePath.string());
		if (pContent == nullptr) return;

		const std::type_info& type = pContent->GetType();
		size_t hashCode = type.hash_code();

		GUID newGUID;
		if (CoCreateGuid(&newGUID) != S_OK) return;
		pContent->m_GUID = newGUID;

		Serialization::BaseSerializer* hashCodeSerializer = Serialization::Serializer::GetSerializer(typeid(size_t));
		Serialization::BaseSerializer* guidSerializer = Serialization::Serializer::GetSerializer(typeid(GUID));

		std::ofstream fStream(metaFilePath.string());
		std::any hashCodeAny = hashCode;
		std::any guidAny = newGUID;
		hashCodeSerializer->Serialize(hashCodeAny, fStream);
		guidSerializer->Serialize(guidAny, fStream);
		fStream.close();

		// TODO: Make the path relative to the asset/resource path!
		GetInstance()->m_AssetPaths[newGUID] = filePath.string();
		AssetManager::AddAsset(pContent);
	}
}
