#include "stdafx.h"
#include "AssetDatabase.h"
#include "AssetManager.h"
#include "Serializer.h"

namespace Spartan
{
	AssetDatabase::AssetDatabase() : m_pDatabaseInstance(nullptr)
	{
		std::string path = BaseGame::GetAssetRootPath() + "/Assets.db";
		m_pDatabaseInstance = LocalDatabase::BeginDatabase(path.c_str());

		//SQLCreateTableDef tableDef;
		//tableDef.Name = "Assets";
		//tableDef.Keys.push_back(SQLTableKeyData());
		//tableDef.Keys[0].Attributes.push_back("PRIMARY KEY");
		//tableDef.Keys[0].Attributes.push_back("NOT NULL");
		//tableDef.Keys[0].Type = "CHAR(32)";
		//tableDef.Keys[0].Name = "GUID";
		//tableDef.Keys.push_back(SQLTableKeyData());
		//tableDef.Keys[1].Attributes.push_back("NOT NULL");
		//tableDef.Keys[1].Type = "INT UNSIGNED";
		//tableDef.Keys[1].Name = "HashCode";
		//tableDef.Keys.push_back(SQLTableKeyData());
		//tableDef.Keys[2].Attributes.push_back("NOT NULL");
		//tableDef.Keys[2].Type = "TEXT";
		//tableDef.Keys[2].Name = "Path";
		//m_pDatabaseInstance->CreateTable(tableDef);

		m_pDatabaseInstance->ExecuteRawCommand("CREATE TABLE Types (TypeID INTEGER PRIMARY KEY AUTOINCREMENT, Name varchar(255) NOT NULL, FullName varchar(255) NOT NULL, HashCode INT UNSIGNED);");
		m_pDatabaseInstance->ExecuteRawCommand("CREATE TABLE Assets (GUID UNIQUEIDENTIFIER PRIMARY KEY, Name varchar(255) NOT NULL, Path TEXT NOT NULL, TypeID INT UNSIGNED, FOREIGN KEY(TypeID) REFERENCES Types(TypeID));");

		//m_pDatabaseInstance->ExecuteRawCommand("INSERT INTO Types (Name, FullName, HashCode) VALUES (\'TEST\', \'SOME_TEST_TYPE\', 648176817);");
	}

	AssetDatabase::~AssetDatabase()
	{
		LocalDatabase::EndDatabase(m_pDatabaseInstance);
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
		LocalDatabase::EndDatabase(pInstance->m_pDatabaseInstance);
		pInstance->m_pDatabaseInstance = LocalDatabase::BeginDatabase("./Resources/Assets.db");
	}

	void AssetDatabase::Refresh()
	{

	}

	void AssetDatabase::DiscoverAssets()
	{
		AssetDatabase* pInstance = GetInstance();

		// Scan asset folder
		ProcessDirectory(BaseGame::GetAssetRootPath());

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
		//for_each(m_AssetPaths.begin(), m_AssetPaths.end(), [&](std::pair<const GUID, std::string>& pair)
		//{
		//	const GUID guid = pair.first;
		//	std::string path = pair.second;
		//});
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
		AssetDatabase* pInstance = GetInstance();

		auto ext = filePath.extension();
		std::filesystem::path metaExtension = std::filesystem::path(".meta");
		if (ext.compare(metaExtension) == 0) return; // No need to process meta files
		auto metaFilePath = filePath;
		metaFilePath = metaFilePath.replace_extension(metaExtension);

		if (std::filesystem::exists(metaFilePath))
		{
			// Both file and meta file exists we need to check if it also exists in the database!
			Serialization::MetaData metaData = Serialization::MetaData::Read(metaFilePath.string());
			//if (pInstance->m_AssetPaths.find(metaData.m_GUID) != pInstance->m_AssetPaths.end()) return;
			if (pInstance->GetAssetPath(metaData.m_GUID) != "") return;

			// Asset is missing from the database
			std::string pathToFile = filePath.string();
			int assetsIndex = pathToFile.find("Assets");
			std::string relativePathToFile = pathToFile.substr(assetsIndex + 6);
			//pInstance->m_AssetPaths[metaData.m_GUID] = relativePathToFile;
			return;
		}

		// Load the file
		Content* pContent = ContentManager::GetInstance()->Load(filePath.string());
		if (pContent == nullptr) return;

		const std::type_info& type = pContent->GetType();
		size_t hashCode = AssetManager::GetAssetHash(type);

		// Make the path relative to the asset/resource path!
		std::string pathToFile = filePath.string();
		int assetsIndex = pathToFile.find("Assets");
		std::string relativePathToFile = pathToFile.substr(assetsIndex + 6);

		// Add the asset to the database and retreive the GUID
		GUID newGUID = pInstance->AddAsset(type, filePath.filename().string(), relativePathToFile);
		pContent->m_GUID = newGUID;

		Serialization::MetaData metaData = Serialization::MetaData(hashCode, newGUID, metaFilePath.string());
		metaData.Write();

		AssetManager::AddAsset(pContent);
	}

	size_t AssetDatabase::GetTypeID(const std::type_info& type)
	{
		if (!m_pDatabaseInstance->Select("Types")) return 0; // Something went wrong

		const SQLSelectResult& result = m_pDatabaseInstance->GetSelectResult();

		if (result.Data.size() <= 0)
		{
			if (!AddType(type)) return 0; // Something went wrong
			return GetTypeID(type);
		}

		std::string typeIDString = result.Data[0].at("TypeID");
		long long longID = stoll(typeIDString);
		return (size_t)longID;
	}

	bool AssetDatabase::AddType(const std::type_info& type)
	{
		size_t hashCode = AssetManager::GetAssetHash(type);
		if (!m_pDatabaseInstance->Select("Types", "*", "WHERE HashCode = " + to_string(hashCode))) return false; // Something went wrong
		const SQLSelectResult& result = m_pDatabaseInstance->GetSelectResult();
		if (result.Data.size() > 0) return true; // Type already exists!
		std::string name = type.name();
		std::string rawName = type.name();
		return m_pDatabaseInstance->ExecuteRawCommand("INSERT INTO Types (Name, FullName, HashCode) VALUES (\'" + name + "\', \'" + rawName + "\', " + to_string(hashCode) + ");");
	}

	std::string AssetDatabase::GetAssetPath(const GUID& guid)
	{
		std::string guidString = GuidToString(guid);
		if (!m_pDatabaseInstance->Select("Assets", "Path", "WHERE GUID = \'" + guidString + "\';")) return ""; // Something went wrong
		const SQLSelectResult& result = m_pDatabaseInstance->GetSelectResult();
		if (result.Data.size() <= 0) return ""; // Asset does not exist!
		return result.Data[0].at("Path");
	}

	GUID AssetDatabase::AddAsset(const std::type_info& assetType, const std::string& name, const std::string& path)
	{
		GUID newGUID;
		if (CoCreateGuid(&newGUID) != S_OK)
		{
			throw new exception("Can't create a new GUID!");
		}
		size_t typeID = GetTypeID(assetType);
		std::string cmd = "INSERT INTO Assets (GUID, Name, Path, TypeID) VALUES (\'" + GuidToString(newGUID) + "\', \'" + name + "\', \'" + path + "\', " + to_string(typeID) + ");";
		if (!m_pDatabaseInstance->ExecuteRawCommand(cmd)) return GUID();
		return newGUID;
	}

	GUID AssetDatabase::StringToGuid(const std::string& str)
	{
		GUID guid;
		sscanf_s(str.c_str(),
			"%8x-%4hx-%4hx-%2hhx%2hhx-%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx",
			&guid.Data1, &guid.Data2, &guid.Data3,
			&guid.Data4[0], &guid.Data4[1], &guid.Data4[2], &guid.Data4[3],
			&guid.Data4[4], &guid.Data4[5], &guid.Data4[6], &guid.Data4[7]);

		return guid;
	}

	std::string AssetDatabase::GuidToString(GUID guid)
	{
		char guid_cstr[39];
		snprintf(guid_cstr, sizeof(guid_cstr),
			"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

		return std::string(guid_cstr);
	}
}
