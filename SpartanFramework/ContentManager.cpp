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
		AddLoader(new GradientLoader());
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