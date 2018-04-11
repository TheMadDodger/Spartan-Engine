#include "stdafx.h"
#include "../../stdafx.h"
#include "BaseComponent.h"
#include "../Scenes/GameObject.h"

BaseComponent::BaseComponent()
{
}


BaseComponent::~BaseComponent()
{
}

void BaseComponent::RootInitialize(const GameContext & gameContext)
{
	// User defined Initialize()
	Initialize(gameContext);
}

void BaseComponent::RootUpdate(const GameContext & gameContext)
{
	// User defined Update()
	Update(gameContext);
}

void BaseComponent::RootDraw(const GameContext & gameContext)
{
	// User defined Draw()
	Draw(gameContext);
}

void BaseComponent::SetGameObject(GameObject *pObject)
{
	if (pObject != nullptr)
		m_pGameObject = pObject;
}
