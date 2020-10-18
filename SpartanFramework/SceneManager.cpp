#include "stdafx.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "GameScene.h"

namespace Spartan
{
	GameScene* SceneManager::GetActiveScene() const
	{
		return m_pActiveScene;
	}

	void SceneManager::LoadScene(size_t buildIndex, LoadSceneMode mode)
	{
		// Check if out of array
		if (buildIndex >= m_BuildScenes.size())
		{
			Utilities::Debug::LogError("SceneManager::LoadScene > The scene build index " + to_string(buildIndex) + " is out of range");
			return;
		}
		m_LoadOperations.push(LoadOperation(mode, buildIndex));
	}

	void SceneManager::LoadScene(const std::string& sceneName, LoadSceneMode mode)
	{
		// Find the index of this scene
		size_t index = 0;
		auto it = find_if(m_BuildScenes.begin(), m_BuildScenes.end(), [sceneName, &index](const Scene& scene)
		{
			if (scene.m_Name == sceneName)
			{
				return true;
			}
			else
			{
				++index;
				return false;
			}
		});

		if (it == m_BuildScenes.end())
		{
			Utilities::Debug::LogWarning("Scene with name " + sceneName + " does not exist!");
			return;
		}

		LoadScene(index, mode);
	}

	void SceneManager::Initialize(const GameContext& gameContext)
	{
		// TODO: Load scenes file
	}

	void SceneManager::Update(const GameContext& gameContext)
	{
		while (!m_LoadOperations.empty())
		{
			LoadOperation loadOperation = m_LoadOperations.front();
			HandleLoadOperation(loadOperation);
			m_LoadOperations.pop();
		}

		for (auto pScene : m_pLoadedScenes)
		{
			pScene->RootUpdate(gameContext);
		}
	}

	void SceneManager::Draw(const GameContext& gameContext)
	{
		for (auto pScene : m_pLoadedScenes)
		{
			pScene->RootDraw(gameContext);
		}
	}

	void SceneManager::UnloadAll()
	{
		for (auto pScene : m_pLoadedScenes)
		{
			delete pScene;
		}
		m_pLoadedScenes.clear();
		m_pActiveScene = nullptr;
	}

	void SceneManager::HandleLoadOperation(const LoadOperation& operation)
	{
		if (operation.m_Unload)
		{
			HandleUnLoadOperation(operation);
			return;
		}

		if (operation.m_Mode == LoadSceneMode::Single)
		{
			UnloadAll();
		}

		// Make a copy of the vector containing all the persistent objects
		std::vector<GameObject*> persistentObjects = m_pActiveScene->m_pPersistentChildren;

		// Call the RootOnDeActive() event
		m_pActiveScene->RootOnDeActive();
		// Clear the current scene
		m_pActiveScene->RootCleanup();

		// Update m_CurrentScene
		//m_CurrentScene = sceneIndex;

		// Pass through persistent objects
		//m_pScenes[m_CurrentScene]->m_pPersistentChildren = persistentObjects;

		// Enable the scene
		//m_pScenes[m_CurrentScene]->SetEnabled(true);
	}

	void SceneManager::HandleUnLoadOperation(const LoadOperation& operation)
	{

	}

	SceneManager::SceneManager()
	{
	}

	SceneManager::~SceneManager()
	{
		UnloadAll();
		//m_BuildSceneGUIDs.clear();
		//m_BuildSceneNames.clear();
	}

	LoadOperation::LoadOperation(LoadSceneMode mode, size_t buildIndex, bool unload) : m_Mode(mode), m_BuildIndex(buildIndex), m_Unload(unload) {}
	Scene::Scene(const std::string& path, const std::string& name, int buildIndex) : m_Path(path), m_Name(name), m_BuildIndex(buildIndex) {}
}