#include "stdafx.h"
#include "../../stdafx.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "GameScene.h"

SceneManager *SceneManager::m_pSceneManager = nullptr;

GameScene * SceneManager::GetCurrentScene() const
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

SceneManager * SceneManager::GetInstance()
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

void SceneManager::Initialize(const GameContext & gameContext)
{
	if (m_pScenes.empty())
		return;

	m_pScenes[m_CurrentScene]->RootInitialize(gameContext);
}

void SceneManager::Update(const GameContext & gameContext)
{
	if (m_pScenes.empty())
		return;

	m_pScenes[m_CurrentScene]->RootUpdate(gameContext);
}

void SceneManager::Draw(const GameContext & gameContext)
{
	if (m_pScenes.empty())
		return;

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
