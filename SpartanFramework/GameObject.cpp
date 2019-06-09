#include "stdafx.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "GameScene.h"

GameObject::GameObject(const char *name) : m_pTransform(new TransformComponent()), m_Tag("")
{
	memcpy(m_Name, name, strlen(name));
	AddComponent(m_pTransform);
}

GameObject::~GameObject()
{
	for (auto pChild : m_pChildren)
	{
		pChild->OnDestroy();
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

void GameObject::RemoveChild(GameObject *pChild)
{
	auto it = find(m_pChildren.begin(), m_pChildren.end(), pChild);
	if (it == m_pChildren.end()) return;

	m_pChildren.erase(it);

	/*if (deleteObject)
	{
		delete pChild;
		pChild = nullptr;
	}*/
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

const std::string & GameObject::GetTag()
{
	return m_Tag;
}

void GameObject::SetTag(const std::string &tag)
{
	m_Tag = tag;
}

bool GameObject::IsEnabled()
{
	return m_Enabled;
}

void GameObject::SetEnabled(bool enabled)
{
	if (m_Enabled != enabled)
	{
		if (m_Enabled)
			OnEnable();
		else
			OnDisable();
	}
	m_Enabled = enabled;
}

void GameObject::SetName(const char *name)
{
	ZeroMemory(m_Name, strlen(m_Name));
	memcpy(m_Name, name, strlen(name));
}

void GameObject::RootInitialize(const GameContext &gameContext)
{
	if (m_bInitialized) return;

	// User defined Initialize()
	Initialize(gameContext);

	for (auto pComponent : m_pComponents)
	{
		pComponent->RootInitialize(gameContext);
	}

	for (auto pChild : m_pChildren)
	{
		pChild->RootInitialize(gameContext);
	}

	m_bInitialized = true;
}

void GameObject::RootPostInitialize(const GameContext &gameContext)
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->PostInitialize(gameContext);
	}

	for (auto pChild : m_pChildren)
	{
		pChild->RootPostInitialize(gameContext);
	}

	PostInitialize(gameContext);
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
		if (pChild->IsEnabled())
			pChild->RootUpdate(gameContext);
	}

	// User defined Update()
	Update(gameContext);
}

void GameObject::RootDraw(const GameContext & gameContext)
{
	// User defined Draw()
	Draw(gameContext);

	for (auto pComponent : m_pComponents)
	{
		pComponent->RootDraw(gameContext);
	}

	for (auto pChild : m_pChildren)
	{
		if (pChild->IsEnabled())
			pChild->RootDraw(gameContext);
	}
}

void GameObject::RootCleanup()
{
	for (auto pComp : m_pComponents)
	{
		pComp->RootCleanup();
	}
}

void GameObject::SetParent(GameObject *pParent)
{
	m_pParentObject = pParent;
}
