#include "stdafx.h"
#include "../../stdafx.h"
#include "GameObject.h"
#include "../Components/BaseComponent.h"
#include "../Components/TransformComponent.h"
#include "GameScene.h"

GameObject::GameObject() : m_pTransform(new TransformComponent())
{
	AddComponent(m_pTransform);
}

GameObject::~GameObject()
{
	for (auto pChild : m_pChildren)
	{
		delete pChild;
	}
	m_pChildren.clear();

	for (auto pComponent : m_pComponents)
	{
		delete pComponent;
	}

	m_pComponents.clear();
}

void GameObject::AddChild(GameObject *pChild, bool initialize)
{
	m_pChildren.push_back(pChild);
	pChild->SetParent(this);
	pChild->m_pScene = m_pScene;

	if (initialize)
	{
		pChild->RootInitialize(BaseGame::GetGame()->GetGameContext());
	}
}

void GameObject::RemoveChild(GameObject *pChild, bool deleteObject)
{
	auto it = find(m_pChildren.begin(), m_pChildren.end(), pChild);
	if (it == m_pChildren.end()) return;

	m_pChildren.erase(it);

	if (deleteObject)
	{
		delete pChild;
		pChild = nullptr;
	}
}

BaseComponent *GameObject::AddComponent(BaseComponent *pComponent)
{
	if (pComponent != nullptr)
	{
		m_pComponents.push_back(pComponent);
		pComponent->SetGameObject(this);
	}
	return pComponent;
}

GameScene *GameObject::GetGameScene() const
{
	return m_pScene;
}

GameObject *GameObject::GetChild(size_t index)
{
	if (index < m_pChildren.size())
		return m_pChildren[index];

	return nullptr;
}

const vector<GameObject*>& GameObject::GetChildren()
{
	return m_pChildren;
}

void GameObject::RootInitialize(const GameContext &gameContext)
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->RootInitialize(gameContext);
	}

	for (auto pChild : m_pChildren)
	{
		pChild->RootInitialize(gameContext);
	}

	// User defined Initialize()
	Initialize(gameContext);

	m_bInitialized = true;
}

void GameObject::RootUpdate(const GameContext &gameContext)
{
	if (!m_bInitialized) // If we haven't initialised yet
	{
		// We initialize
		RootInitialize(gameContext);
	}

	for (auto pComponent : m_pComponents)
	{
		pComponent->RootUpdate(gameContext);
	}

	for (auto pChild : m_pChildren)
	{
		pChild->RootUpdate(gameContext);
	}

	// User defined Update()
	Update(gameContext);
}

void GameObject::RootDraw(const GameContext & gameContext)
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->RootDraw(gameContext);
	}

	for (auto pChild : m_pChildren)
	{
		pChild->RootDraw(gameContext);
	}

	// User defined Draw()
	Draw(gameContext);
}

void GameObject::SetParent(GameObject *pParent)
{
	m_pParentObject = pParent;
}
