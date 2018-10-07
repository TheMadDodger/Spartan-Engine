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

	// Delete the physics world (if it exists)
	if (m_pPhysicsWorld)
	{
		delete m_pPhysicsWorld;
		m_pPhysicsWorld = nullptr;
	}
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

void GameScene::SetActiveCamera(CameraComponent *pCamera)
{
	if(m_pActiveCamera)
		m_pActiveCamera->m_bActive = false;

	m_pActiveCamera = pCamera;
	pCamera->m_bActive = true;
}

void GameScene::RootInitialize(const GameContext &gameContext)
{
	// User Pre-Initialize
	PreInitialize(gameContext);

	// Create default camera
	m_pDefaultCamera = new BasicCamera();
	auto pCam = new CameraComponent();
	m_pDefaultCamera->AddComponent(pCam);
	AddChild(m_pDefaultCamera);
	pCam->SetAsActive();

	// Create the physics world for this scene
	m_Gravity = b2Vec2(0.0f, -9.81f);
	m_pPhysicsWorld = new b2World(m_Gravity);

	// User defined Initialize()
	Initialize(gameContext);

	for (auto pChild : m_pChildren)
	{
		pChild->RootInitialize(gameContext);
	}

	// User Post-Initialize
	PostInitialize(gameContext);
}

void GameScene::RootUpdate(const GameContext &gameContext)
{
	// User Pre-Update
	PreUpdate(gameContext);

	// Update physics world
	float32 timeStep = 1.0f / FixedUpdateSpeed;
	m_pPhysicsWorld->Step(timeStep, Box2DVelocityIterations, Box2DPositionIterations);

	for (auto pChild : m_pChildren)
	{
		pChild->RootUpdate(gameContext);
	}

	// User defined Update()
	Update(gameContext);

	// User Post-Update
	PostUpdate(gameContext);
}

void GameScene::RootDraw(const GameContext &gameContext)
{
	// User Pre-Draw
	PreDraw(gameContext);

	for (auto pChild : m_pChildren)
	{
		pChild->RootDraw(gameContext);
	}

	// User defined Draw()
	Draw(gameContext);

	// User Post-Draw
	PostDraw(gameContext);
}

void GameScene::RootOnActive()
{
	OnActive();
}

void GameScene::RootOnDeActive()
{
	OnDeActive();
}

void GameScene::RootCleanup()
{
	// Clear the objects list
	for (auto pChild : m_pChildren)
	{
		delete pChild;
	}

	m_pChildren.clear();

	// Delete the physics world (if it exists)
	if (m_pPhysicsWorld)
	{
		delete m_pPhysicsWorld;
		m_pPhysicsWorld = nullptr;
	}

	// User defined cleanup method
	Cleanup();
}
