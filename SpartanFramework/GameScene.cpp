#include "stdafx.h"
#include "GameScene.h"
#include "GameObject.h"
#include "BasicCamera.h"
#include "CameraComponent.h"

GameScene::GameScene(const std::string &name) : m_SceneName(name)
{
}

GameScene::~GameScene()
{
	for (auto pChild : m_pChildren)
	{
		pChild->RootCleanup();
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

void GameScene::AddChild(GameObject *pObject, bool bForceInitialize)
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

	if (bForceInitialize)
	{
		pObject->RootInitialize(BaseGame::GetGame()->GetGameContext());
	}
}

void GameScene::RemoveChild(GameObject *pObject)
{
	auto it = find(m_pChildren.begin(), m_pChildren.end(), pObject);
	if (it == m_pChildren.end()) return;

	m_pChildren.erase(it);
}

void GameScene::SetActiveCamera(CameraComponent *pCamera)
{
	if(m_pActiveCamera)
		m_pActiveCamera->m_bActive = false;

	m_pActiveCamera = pCamera;
	pCamera->m_bActive = true;
}

void GameScene::DontDestroyOnLoad(GameObject *pObject)
{
	pObject->m_Persistent = true;
	m_pPersistentChildren.push_back(pObject);
}

void GameScene::Destroy(GameObject *gameObject)
{
	m_pQueuedForDestruction.push_back(gameObject);
}

void GameScene::Instantiate(GameObject *gameObject, GameObject *pParent)
{
	m_pInstantiateQueue.push_back(Instantiation(gameObject, pParent));
}

void GameScene::SetEnabled(bool enabled)
{
	m_bEnabled = enabled;
}

void GameScene::RootInitialize(const GameContext &gameContext)
{
	// User Pre-Initialize
	PreInitialize(gameContext);

	// Create default camera
	m_pDefaultCamera = new BasicCamera();
	m_pDefaultCamera->SetName("Main Camera");
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

	for (auto pChild : m_pChildren)
	{
		pChild->RootPostInitialize(gameContext);
	}

	// User Post-Initialize
	PostInitialize(gameContext);
}

void GameScene::RootUpdate(const GameContext &gameContext)
{
	if (!m_bEnabled) return;

	// User Pre-Update
	PreUpdate(gameContext);

	// Update physics world
	float32 timeStep = 1.0f / FixedUpdateSpeed;
	m_pPhysicsWorld->Step(timeStep, Box2DVelocityIterations, Box2DPositionIterations);

	for (auto pChild : m_pChildren)
	{
		if(pChild->IsEnabled())
			pChild->RootUpdate(gameContext);
	}

	// User defined Update()
	Update(gameContext);

	// User Post-Update
	PostUpdate(gameContext);

	// Destroy all objects that were marked for destruction last frame
	DestroyObjects();

	// Spawn all objects that were Instantiated last frame
	InstantiateObjects(gameContext);
}

void GameScene::RootDraw(const GameContext &gameContext)
{
	if (!m_bEnabled) return;

	// User Pre-Draw
	PreDraw(gameContext);

	for (auto pChild : m_pChildren)
	{
		if (pChild->IsEnabled())
			pChild->RootDraw(gameContext);
	}

	// User defined Draw()
	Draw(gameContext);

	// User Post-Draw
	PostDraw(gameContext);
}

void GameScene::LoadPersistent()
{
	std::for_each(m_pPersistentChildren.begin(), m_pPersistentChildren.end(), [&](GameObject *pChild)
	{
		AddChild(pChild);
	});
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
		if(!pChild->m_Persistent)
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

void GameScene::DestroyObjects()
{
	for (auto gameObject : m_pQueuedForDestruction)
	{
		gameObject->OnDestroy();
		if (gameObject->GetParent() != nullptr)
		{
			gameObject->GetParent()->RemoveChild(gameObject);
		}
		else
		{
			RemoveChild(gameObject);
		}
		delete gameObject;
	}

	m_pQueuedForDestruction.clear();
}

void GameScene::InstantiateObjects(const GameContext &gameContext)
{
	for (auto instantiate : m_pInstantiateQueue)
	{
		if (instantiate.Parent != nullptr)
		{
			instantiate.Parent->AddChild(instantiate.Object);
			instantiate.Object->RootInitialize(gameContext);
		}
		else
		{
			AddChild(instantiate.Object);
		}
		instantiate.Object->OnCreated();
	}

	m_pInstantiateQueue.clear();
}
