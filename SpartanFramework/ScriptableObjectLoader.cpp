#include "stdafx.h"
#include "ScriptableObjectLoader.h"
#include "AssetManager.h"
#include "AssetDatabase.h"

namespace Spartan
{
    ScriptableObjectLoader::ScriptableObjectLoader() : ContentLoader({ ".sasset" })
    {
    }

    ScriptableObjectLoader::~ScriptableObjectLoader()
    {
    }

    bool ScriptableObjectLoader::SaveContent(Serialization::BaseAsset* pAsset, const std::string& path)
    {
        std::ofstream fileStream;
        fileStream.open(path);
        if (!fileStream.is_open())
        {
            Utilities::Debug::LogWarning("Can't open " + path);
            return false;
        }

        pAsset->Serialize(fileStream);
        fileStream.close();
        return true;
    }

    Serialization::BaseAsset* ScriptableObjectLoader::LoadContent(const std::string& file)
    {
        std::ifstream fileStream;
        fileStream.open(file);
        if (!fileStream.is_open())
        {
            Utilities::Debug::LogWarning("Can't open " + file);
            return nullptr;
        }

        size_t assetHash;
        GUID assetGUID;
        fileStream.read((char*)&assetHash, sizeof(size_t));
        fileStream.read((char*)&assetGUID, sizeof(GUID));
        
        // TODO: Check if the GUID already exists
        Content* pAsset = (Serialization::BaseAsset*)SEObject::CreateObject(assetHash);
        if (pAsset == nullptr)
        {
            Utilities::Debug::LogWarning("Unable to make an instance of this type, make sure the asset class is registered in your project! \n" + file);
            return nullptr;
        }
        pAsset->m_GUID = assetGUID;
        Serialization::BaseAsset* pDeserializedAsset = (Serialization::BaseAsset*)pAsset;
        pDeserializedAsset->Deserialize(fileStream, 2);
        fileStream.close();
        return pDeserializedAsset;
    }
}