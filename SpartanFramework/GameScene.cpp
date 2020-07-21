#include "stdafx.h"
#include "GameScene.h"
#include "BasicCamera.h"
#include "CameraComponent.h"
#include "Layers.h"

namespace Spartan
{
	GameScene::GameScene(const std::string& name) : m_SceneName(name)
	{
	}

	GameScene::~GameScene()
	{
		m_pLayers.clear();

		for (size_t i = 0; i < m_pChildren.size(); ++i)
		{
			auto pChild = m_pChildren[i];
			pChild->OnDestroy();
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

	void GameScene::AddChild(GameObject* pObject)
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

	void GameScene::RemoveChild(GameObject* pObject)
	{
		auto it = find(m_pChildren.begin(), m_pChildren.end(), pObject);
		if (it == m_pChildren.end()) return;

		m_pChildren.erase(it);
	}

	void GameScene::SetActiveCamera(CameraComponent* pCamera)
	{
		if (m_pActiveCamera)
			m_pActiveCamera->m_bActive = false;

		m_pActiveCamera = pCamera;
		pCamera->m_bActive = true;
	}

	void GameScene::DontDestroyOnLoad(GameObject* pObject)
	{
		pObject->m_Persistent = true;
		m_pPersistentChildren.push_back(pObject);
	}

	void GameScene::Destroy(GameObject* pGameObject)
	{
		if (!pGameObject) return;

		for (size_t i = 0; i < pGameObject->m_pChildren.size(); i++)
		{
			Destroy(pGameObject->GetChild(i));
		}

		pGameObject->OnDestroy();

		if (pGameObject->GetParent())
		{
			pGameObject->GetParent()->RemoveChild(pGameObject);
		}
		else
		{
			RemoveChild(pGameObject);
		}

		delete pGameObject;
		pGameObject = nullptr;
	}

	GameObject* GameScene::Instantiate(GameObject* pObject, GameObject* pParent)
	{
		pObject->m_pScene = this;
		if (pParent != nullptr)
		{
			pParent->AddChild(pObject);
			return nullptr;
		}

		AddChild(pObject);
		UpdateLayers(pObject, -1, pObject->GetLayer().LayerID);
		return pObject;
	}

	void GameScene::SetEnabled(bool enabled)
	{
		m_bEnabled = enabled;
	}

	void GameScene::RootInitialize(const GameContext& gameContext)
	{
		for (size_t i = 0; i < LayerManager::GetInstance()->Size(); i++)
		{
			m_pLayers.push_back(std::list<GameObject*>());
		}

		// User Pre-Initialize
		PreInitialize(gameContext);

		// Create default camera
		m_pDefaultCamera = new BasicCamera();
		m_pDefaultCamera->SetName("Main Camera");
		m_pDefaultCamera->GetCameraComponent()->SetPerspective(60.0f * M_PI / 180.0f, 0.1f, 99999.0f);
		m_pDefaultCamera->RootInitialize(gameContext);
		AddChild(m_pDefaultCamera);

		m_pDefaultCamera->GetCameraComponent()->SetPerspective(60.0f, 0.1f, 999999.0f);
		m_pDefaultCamera->GetCameraComponent()->SetAsActive();

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

	void GameScene::RootUpdate(const GameContext& gameContext)
	{
		if (!m_bEnabled) return;

		// User Pre-Update
		PreUpdate(gameContext);

		// Update physics world
		float32 timeStep = 1.0f / FixedUpdateSpeed;
		m_pPhysicsWorld->Step(timeStep, Box2DVelocityIterations, Box2DPositionIterations);

		// Since the child count at the start of the frame can change during a frames update
		// We need to copy the objects to an array that won't change
		// Otherwise we crash when an object is destroyed or instantiated during this frame!!!
		size_t childCountThisFrame = m_pChildren.size();
		GameObject** pChildrenArray = new GameObject * [childCountThisFrame];
		std::copy(m_pChildren.begin(), m_pChildren.end(), pChildrenArray);
		for (size_t i = 0; i < childCountThisFrame; ++i)
		{
			auto pChild = pChildrenArray[i];

			if (pChild->IsEnabled())
				pChild->RootUpdate(gameContext);
		}

		// Delete the allocated array cus yea memory leaks ya kno
		delete[] pChildrenArray;

		// User defined Update()
		Update(gameContext);

		// User Post-Update
		PostUpdate(gameContext);
	}

	void GameScene::RootDraw(const GameContext& gameContext)
	{
		if (!m_bEnabled) return;

		// User Pre-Draw
		PreDraw(gameContext);

		// Rendering layer by layer
		for (size_t i = 0; i < m_pLayers.size(); i++)
		{
			RenderLayer(gameContext, m_pLayers[i]);
		}

		// User defined Draw()
		Draw(gameContext);

		// User Post-Draw
		PostDraw(gameContext);
	}

	void GameScene::RenderLayer(const GameContext& gameContext, std::list<GameObject*> pObjectsOnLayer)
	{
		for (GameObject* pChild : pObjectsOnLayer)
		{
			if (pChild->IsEnabled())
				pChild->RootDraw(gameContext);
		}
	}

	void GameScene::LoadPersistent()
	{
		std::for_each(m_pPersistentChildren.begin(), m_pPersistentChildren.end(), [&](GameObject* pChild)
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
			if (!pChild->m_Persistent)
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

	void GameScene::UpdateLayers(GameObject* pObject, int oldLayer, int newLayer)
	{
		if (oldLayer != -1)
			m_pLayers[oldLayer].remove(pObject);

		m_pLayers[newLayer].push_back(pObject);
	}
}
