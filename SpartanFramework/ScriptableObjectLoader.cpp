#include "stdafx.h"
#include "ScriptableObjectLoader.h"

namespace Spartan
{
    ScriptableObjectLoader::ScriptableObjectLoader() : ContentLoader({ ".sasset" })
    {
    }

    ScriptableObjectLoader::~ScriptableObjectLoader()
    {
    }

    Serialization::BaseAsset* ScriptableObjectLoader::LoadContent(const std::string& file)
    {
        return nullptr;
    }
}