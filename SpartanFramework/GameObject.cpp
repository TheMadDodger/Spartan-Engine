#include "stdafx.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "GameScene.h"
#include "Layers.h"

namespace SpartanEngine
{
	GameObject::GameObject(const char* name, size_t layerID)
		: m_pComponents(std::vector<BaseComponent*>()),
		m_pChildren(std::vector<GameObject*>()),
		m_Tag(""), m_LayerID(layerID), m_IsDirty(true)
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

	void GameObject::SetFullDirty()
	{
		bool hasChildren = false;
		for (auto pChild : GetChildren())
		{
			pChild->SetFullDirty();
			hasChildren = true;
		}
		if (hasChildren) return;
		SetDirty();
	}

	void GameObject::AddChild(GameObject* pChild)
	{
		m_pChildren.push_back(pChild);
		pChild->m_pParentObject = this;
		pChild->m_pScene = m_pScene;
		pChild->OnParentUpdated(this);
	}

	void GameObject::RemoveChild(GameObject* pChild)
	{
		auto it = find(m_pChildren.begin(), m_pChildren.end(), pChild);
		if (it == m_pChildren.end()) return;

		m_pChildren.erase(it);
		pChild->m_pParentObject = nullptr;
		pChild->OnParentUpdated(nullptr);
	}

	void GameObject::SetDirty(bool dirty)
	{
		m_IsDirty = dirty;
		if (!dirty || m_pParentObject == nullptr) return;
		m_pParentObject->SetDirty();
	}

	void GameObject::SetScene(SpartanEngine::GameScene* pScene)
	{
		m_pScene = pScene;
		for (size_t i = 0; i < m_pChildren.size(); i++)
		{
			m_pChildren[i]->SetScene(pScene);
		}
	}

	GameScene* GameObject::GetGameScene() const
	{
		return m_pScene;
	}

	GameObject* GameObject::GetChild(size_t index) const
	{
		if (index < m_pChildren.size())
			return m_pChildren[index];

		return nullptr;
	}

	const vector<GameObject*>& GameObject::GetChildren() const
	{
		return m_pChildren;
	}

	const std::string& GameObject::GetTag() const
	{
		return m_Tag;
	}

	void GameObject::SetTag(const std::string& tag)
	{
		m_Tag = tag;
	}

	bool GameObject::IsEnabled() const
	{
		return m_Enabled;
	}

	void GameObject::SetEnabled(bool enabled)
	{
		if (m_Enabled != enabled)
		{
			m_Enabled = enabled;
			if (m_Enabled)
			{
				RootOnEnable();
			}
			else
				RootOnDisable();
		}

		if (!m_Enabled)
		{
			SetDirty(false);
			auto pParent = GetParent();
			if (pParent) pParent->SetDirty();
			return;
		}

		SetDirty();
	}

	void GameObject::SetName(const char* name)
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

	bool GameObject::IsDirty() const
	{
		if (m_IsDirty) return true;
		for (size_t i = 0; i < m_pChildren.size(); i++)
		{
			if (m_pChildren[i]->IsDirty()) return true;
		}
		return false;
	}

	void GameObject::SetDirty()
	{
		SetDirty(true);
	}

	void GameObject::RootInitialize(const GameContext& gameContext)
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
			pChild->OnParentUpdated(this);
			pChild->RootInitialize(gameContext);
		}

		m_bInitialized = true;
	}

	void GameObject::RootPostInitialize(const GameContext& gameContext)
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

	void GameObject::RootUpdate(const GameContext& gameContext)
	{
		if (!m_bInitialized) // If we haven't initialised yet
		{
			// We initialize
			RootInitialize(gameContext);
		}

		BeginUpdate(gameContext);

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

	void GameObject::RootDraw(const GameContext& gameContext)
	{
		if (!m_bInitialized) return;

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

		PostDraw(gameContext);
	}

	void GameObject::UIHandleMouse(const Vector2& relativeMousePos)
	{
		Matrix4X4 matLocalInverse = GetTransform()->GetLocalTransformMatrix().Inverse();

		Vector4 mousePosVec4 = Vector4(relativeMousePos.x, relativeMousePos.y, 0.0f, 1.0f);
		Vector2 localMousePos = (matLocalInverse * mousePosVec4).xy();

		//Utilities::Debug::LogInfo("Relative: " + to_string(relativeMousePos.x) + ", " + to_string(relativeMousePos.y) + ", Local: " + to_string(localMousePos.x) + ", " + to_string(localMousePos.y));
		PassUIMouseInputToChildren(localMousePos);
	}

	void GameObject::PassUIMouseInputToChildren(const Vector2& localMousePos)
	{
		std::for_each(m_pChildren.begin(), m_pChildren.end(), [&](GameObject* pChild) {pChild->UIHandleMouse(localMousePos); });
	}

	void GameObject::RootOnEnable()
	{
		for (size_t i = 0; i < GetChildren().size(); i++)
		{
			auto pChild = GetChild(i);
			if (!pChild->IsEnabled()) continue;
			pChild->OnEnable();
		}
		OnEnable();
	}

	void GameObject::RootOnDisable()
	{
		for (size_t i = 0; i < GetChildren().size(); i++)
		{
			auto pChild = GetChild(i);
			if (!pChild->IsEnabled()) continue;
			pChild->OnDisable();
		}
		OnDisable();
	}

	void GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
	{
		if (m_pParentObject)
			m_pParentObject->RemoveChild(this);

		if (pParent)
		{
			GetGameScene()->RemoveChild(this);
			pParent->AddChild(this);

			if (keepWorldPosition)
			{
				auto newPos = GetTransform()->GetWorldPosition() - pParent->GetTransform()->GetWorldPosition();
				GetTransform()->Translate(newPos, true);
			}
		}
		else
		{
			GetGameScene()->AddChild(this);

			if (keepWorldPosition)
			{
				auto newPos = GetTransform()->GetWorldPosition();
				GetTransform()->Translate(newPos, true);
			}
		}
	}
}