#include "stdafx.h"
#include "BaseComponent.h"
#include "GameObject.h"

namespace SpartanEngine
{
	std::vector<BaseComponent*> BaseComponent::m_pRegisteredComponents = std::vector<BaseComponent*>();

	BaseComponent::BaseComponent(const char* name) : m_Name(name)
	{
	}

	BaseComponent::~BaseComponent()
	{
	}

	void BaseComponent::Register(BaseComponent* pComponent)
	{
		m_pRegisteredComponents.push_back(pComponent);
	}

	BaseComponent* BaseComponent::CreateFromName(const std::string& name)
	{
		auto it = std::find_if(m_pRegisteredComponents.begin(), m_pRegisteredComponents.end(), [&](BaseComponent* pComp)
		{
			if (pComp->GetName() == name)
				return true;
			return false;
		});

		if (it == m_pRegisteredComponents.end()) return nullptr;
		auto pComp = *it;
		return pComp->Create();
	}

	void BaseComponent::RootAwake()
	{
		if (!m_pGameObject) return;
		if (m_bEnabled) return;
		Awake();
		m_bEnabled = true;
	}

	void BaseComponent::RootInitialize(const GameContext& gameContext)
	{
		if (m_bInitialized) return;

		// User defined Initialize()
		Initialize(gameContext);

		m_bInitialized = true;
	}

	void BaseComponent::RootUpdate(const GameContext& gameContext)
	{
		if (!m_bInitialized)
		{
			RootInitialize(gameContext);
		}

		if (!m_bEnabled) return;

		// User defined Update()
		Update(gameContext);
	}

	void BaseComponent::RootDraw(const GameContext& gameContext)
	{
		if (!m_bEnabled) return;

		// User defined Draw()
		Draw(gameContext);
	}

	void BaseComponent::SetGameObject(GameObject* pObject)
	{
		if (pObject != nullptr)
			m_pGameObject = pObject;
	}
}