#include "stdafx.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "GameScene.h"

SceneManager *SceneManager::m_pSceneManager = nullptr;

GameScene *SceneManager::GetCurrentScene() const
{
	if (m_pScenes.empty())
		return nullptr;
	
	return m_pScenes[m_CurrentScene];
}

void SceneManager::AddScene(GameScene *pScene)
{
	if (pScene != nullptr)
	{
		m_pScenes.push_back(pScene);
	}
}

void SceneManager::LoadScene(int sceneIndex)
{
	// Check if out of array
	if ((size_t)sceneIndex < m_pScenes.size())
	{
		// Make a copy of the vector containing all the persistent objects
		std::vector<GameObject*> persistentObjects = m_pScenes[m_CurrentScene]->m_pPersistentChildren;

		// Call the RootOnDeActive() event
		m_pScenes[m_CurrentScene]->RootOnDeActive();
		// Clear the current scene
		m_pScenes[m_CurrentScene]->RootCleanup();

		// Update m_CurrentScene
		m_CurrentScene = sceneIndex;
		m_SceneHasInitialized = false;

		// Pass through persistent objects
		m_pScenes[m_CurrentScene]->m_pPersistentChildren = persistentObjects;
	}
	else
	{
		Utilities::Debug::LogWarning("Scene with index " + to_string(sceneIndex) + " is out of bounds!");
	}
}

void SceneManager::LoadScene(const std::string &sceneName)
{
	// Find the index of this scene
	int index = 0;
	auto it = find_if(m_pScenes.begin(), m_pScenes.end(), [sceneName, &index](GameScene *pScene)
	{
		if (pScene->GetName() == sceneName)
		{
			return true;
		}
		else
		{
			++index;
			return false;
		}
	});

	if (it == m_pScenes.end())
	{
		Utilities::Debug::LogWarning("Scene with name " + sceneName + " does not exist!");
		return;
	}

	LoadScene(index);
}

SceneManager *SceneManager::GetInstance()
{
	if (m_pSceneManager)
		return m_pSceneManager;

	m_pSceneManager = new SceneManager();
	return m_pSceneManager;
}

void SceneManager::Destroy()
{
	delete m_pSceneManager;
	m_pSceneManager = nullptr;
}

void SceneManager::Initialize(const GameContext &gameContext)
{
	if (m_pScenes.empty())
	{
		Utilities::Debug::LogError("There must be at least 1 scene added to the SceneManager!");
		return;
	}

	m_pScenes[m_CurrentScene]->RootInitialize(gameContext);
	m_pScenes[m_CurrentScene]->LoadPersistent();
	m_SceneHasInitialized = true;

	m_pScenes[m_CurrentScene]->GameStart(gameContext);
}

void SceneManager::Update(const GameContext &gameContext)
{
	// Check if the current scene has been initialized if not do that
	if (!m_SceneHasInitialized)
		Initialize(gameContext);

	m_pScenes[m_CurrentScene]->RootUpdate(gameContext);
}

void SceneManager::Draw(const GameContext &gameContext)
{
	if (!m_SceneHasInitialized) return; // Safety check

	m_pScenes[m_CurrentScene]->RootDraw(gameContext);
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (auto pScene : m_pScenes)
	{
		delete pScene;
	}

	m_pScenes.clear();
}
