#include "stdafx.h"
#include "ContentManager.h"
#include "ContentLoader.h"
#include "TextureLoader.h"
#include "AudioFileLoader.h"
#include "SpriteSheetLoader.h"
#include "FontLoader.h"
#include "ShaderLoader.h"
#include "ModelLoader.h"
#include "GradientLoader.h"
#include "ScriptableObjectLoader.h"

namespace Spartan
{
	ContentManager* ContentManager::m_pContentManager = nullptr;

	ContentManager* ContentManager::GetInstance()
	{
		if (m_pContentManager)
			return m_pContentManager;

		m_pContentManager = new ContentManager();
		return m_pContentManager;
	}

	void ContentManager::Destroy()
	{
		delete m_pContentManager;
		m_pContentManager = nullptr;
	}

	void ContentManager::AddLoader(BaseLoader* pLoader)
	{
		m_pLoaders.push_back(pLoader);
	}

	void ContentManager::Initialize()
	{
		AddLoader(new TextureLoader());
		AddLoader(new AudioFileLoader());
		AddLoader(new SpriteSheetLoader());
		AddLoader(new FontLoader());
		AddLoader(new ShaderLoader());
		AddLoader(new ModelLoader());
		AddLoader(new ScriptableObjectLoader());
		//AddLoader(new GradientLoader());
	}

	Content* ContentManager::Load(const std::string& path)
	{
		std::filesystem::path filePath(path);
		std::filesystem::path extension = filePath.extension();

		for (BaseLoader* pLoader : m_pLoaders)
		{
			if (pLoader->HasExtension(extension.string()))
			{
				Content* pContent = pLoader->Load(path);
				pContent->m_Name = std::filesystem::path(path).filename().replace_extension().string();
				m_pContent.push_back(pContent);
				return pContent;
			}
		}

		return nullptr;
	}

	bool ContentManager::Save(Content* pContent)
	{
		const type_info& type = pContent->GetType();
		for (BaseLoader* pLoader : m_pLoaders)
		{
			if (pLoader->GetType() == type)
			{
				return pLoader->Save(pContent);
			}
		}

		const type_info& baseType = pContent->GetBaseType();
		for (BaseLoader* pLoader : m_pLoaders)
		{
			if (pLoader->GetType() == baseType)
			{
				return pLoader->Save(pContent);
			}
		}

		return false;
	}

	bool ContentManager::Save(Content* pContent, const std::string& path)
	{
		const type_info& type = pContent->GetType();
		for (BaseLoader* pLoader : m_pLoaders)
		{
			if (pLoader->GetType() == type)
			{
				return pLoader->Save(pContent, path);
			}
		}

		const type_info& baseType = pContent->GetBaseType();
		for (BaseLoader* pLoader : m_pLoaders)
		{
			if (pLoader->GetType() == baseType)
			{
				return pLoader->Save(pContent, path);
			}
		}

		return false;
	}

	ContentManager::ContentManager()
	{
	}

	ContentManager::~ContentManager()
	{
		// Clean up content
		for (auto pContent : m_pContent)
		{
			delete pContent;
		}
		m_pContent.clear();

		// Delete loaders
		for (auto pLoader : m_pLoaders)
		{
			delete pLoader;
		}
		m_pLoaders.clear();
	}
}