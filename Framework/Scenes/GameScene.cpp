#include "stdafx.h"
#include "../../stdafx.h"
#include "GameScene.h"
#include "GameObject.h"
#include "BasicCamera.h"
#include "../Components/CameraComponent.h"

GameScene::GameScene(const std::string &name) : m_SceneName(name)
{
}

GameScene::~GameScene()
{
	for (auto pChild : m_pChildren)
	{
		delete pChild;
	}

	m_pChildren.clear();
}

void GameScene::AddChild(GameObject *pObject)
{
	if (pObject != nullptr)
	{
		m_pChildren.push_back(pObject);
		pObject->m_pScene = this;
		for (auto pChild : pObject->m_pChildren)
		{
			pChild->m_pScene = this;
		}
	}
}

void GameScene::SetActiveCamera(CameraComponent * pCamera)
{
	if(m_pActiveCamera)
		m_pActiveCamera->m_bActive = false;

	m_pActiveCamera = pCamera;
}

void GameScene::RootInitialize(const GameContext &gameContext)
{
	// Create default camera
	m_pDefaultCamera = new BasicCamera();
	auto pCam = new CameraComponent();
	m_pDefaultCamera->AddComponent(pCam);
	AddChild(m_pDefaultCamera);
	pCam->SetAsActive();

	// User defined Initialize()
	Initialize(gameContext);

	for (auto pChild : m_pChildren)
	{
		pChild->RootInitialize(gameContext);
	}
}

void GameScene::RootUpdate(const GameContext &gameContext)
{
	for (auto pChild : m_pChildren)
	{
		pChild->RootUpdate(gameContext);
	}

	// User defined Update()
	Update(gameContext);
}

void GameScene::RootDraw(const GameContext &gameContext)
{
	for (auto pChild : m_pChildren)
	{
		pChild->RootDraw(gameContext);
	}

	// User defined Draw()
	Draw(gameContext);
}

void GameScene::RootOnActive(const GameContext &gameContext)
{
	OnActive(gameContext);
}

void GameScene::RootOnDeActive(const GameContext &gameContext)
{
	OnDeActive(gameContext);
}
