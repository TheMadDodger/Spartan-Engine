#pragma once
#include "SerializableAsset.h"

class AssetFactory
{
public:
	template<class T>
	static void RegisterAsset()
	{
		const std::type_info& type = typeid(T);
		size_t hashCode = GetAssetHash<T>();
		auto it = m_AssetTemplates.find(hashCode);
		if (it != m_AssetTemplates.end()) return;
		m_AssetTemplates[hashCode] = new T(GUID());
	}

	template<class T>
	static size_t GetAssetHash()
	{
		const std::type_info& type = typeid(T);
		return GetAssetHash(type);
	}

	static size_t GetAssetHash(const std::type_info& type);

	template<class T>
	static T* CreateInstance()
	{
		const std::type_info& type = typeid(T);
		return (T*)CreateInstance(type);
	}

	static SerializedAsset* CreateInstance(const std::type_info& type);

	static SerializedAsset* DeserializeToAsset(std::ifstream& fileStream);

private:
	static void AddAsset(SerializedAsset* asset);
	static SerializedAsset* GetAssetTemplate(size_t assetHash);

private:
	friend class SerializedAsset;
	AssetFactory() {}
	~AssetFactory() {}

private:
	static std::map<size_t, SerializedAsset*> m_AssetTemplates;
	static std::map<GUID, SerializedAsset*> m_Assets;
	static std::hash<std::string> m_AssetHasher;
};

