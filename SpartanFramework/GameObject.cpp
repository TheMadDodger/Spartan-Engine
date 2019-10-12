#include "stdafx.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "GameScene.h"
#include "Layers.h"

GameObject::GameObject(const char *name, size_t layerID)
	: m_pComponents(std::vector<BaseComponent*>()),
	  m_pChildren(std::vector<GameObject*>()),
	  m_Tag(""), m_LayerID(layerID)
{
	m_pTransform = CreateDefaultComponent<TransformComponent>();

	memcpy(m_Name, name, strlen(name));
	Construct();
}

GameObject::~GameObject()
{
	for (size_t i = 0; i < m_pComponents.size(); ++i)
	{
		auto pComponent = m_pComponents[i];
		pComponent->OnDestroy();
		delete pComponent;
	}
	m_pComponents.clear();

	for (size_t i = 0; i < m_pChildren.size(); ++i)
	{
		auto pChild = m_pChildren[i];
 		pChild->OnDestroy();
		delete pChild;
	}
	m_pChildren.clear();
}

void GameObject::AddChild(GameObject *pChild)
{
	m_pChildren.push_back(pChild);
	pChild->m_pParentObject = this;
	pChild->m_pScene = m_pScene;
}

void GameObject::RemoveChild(GameObject *pChild)
{
	auto it = find(m_pChildren.begin(), m_pChildren.end(), pChild);
	if (it == m_pChildren.end()) return;

	m_pChildren.erase(it);
	pChild->m_pParentObject = nullptr;
}

/*BaseComponent *GameObject::AddComponent(BaseComponent *pComponent)
{
	if (pComponent != nullptr)
	{
		m_pComponents.push_back(pComponent);
		pComponent->SetGameObject(this);
	}
	return pComponent;
}*/

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

const LayerData& GameObject::GetLayer() const
{
	const LayerData& layer = LayerManager::GetInstance()->operator[](m_LayerID);
	return layer;
}

void GameObject::SetLayer(int layerID)
{
	int oldLayer = m_LayerID;
	m_LayerID = layerID;
	GetGameScene()->UpdateLayers(this, oldLayer, m_LayerID);
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

	for (size_t i = 0; i < m_pComponents.size(); ++i)
	{
		auto pComponent = m_pComponents[i];
		pComponent->RootUpdate(gameContext);
	}

	for (size_t i = 0; i < m_pChildren.size(); ++i)
	{
		auto pChild = m_pChildren[i];
		if (pChild->IsEnabled())
			pChild->RootUpdate(gameContext);
	}

	// User defined Update()
	Update(gameContext);
}

void GameObject::RootDraw(const GameContext & gameContext)
{
	// User defined Draw()
	glPushMatrix();
	m_pTransform->ApplyTransform();
	Draw(gameContext);

	for (auto pComponent : m_pComponents)
	{
		pComponent->RootDraw(gameContext);
	}
	glPopMatrix();

	for (auto pChild : m_pChildren)
	{
		if (pChild->IsEnabled())
			pChild->RootDraw(gameContext);
	}
}

void GameObject::SetParent(GameObject *pParent)
{
	if (m_pParentObject->m_pParentObject)
		m_pParentObject->m_pParentObject->RemoveChild(this);

	if (pParent)
	{
		GetGameScene()->RemoveChild(this);
		pParent->AddChild(this);
	}
	else
		GetGameScene()->AddChild(this);
}
