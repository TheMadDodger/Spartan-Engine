#include "stdafx.h"
#include "UIObject.h"
#include "UICanvas.h"
#include "Layers.h"

UIObject::UIObject(const char* name, size_t layerID) : m_pParentCanvas(nullptr), GameObject(name, layerID)
{
}

UIObject::~UIObject()
{
}

UICanvas* UIObject::GetCanvas()
{
	return m_pParentCanvas;
}

void UIObject::OnParentUpdated(GameObject* pNewParent)
{
	GameObject* pParent = GetParent();
	while (pParent != nullptr)
	{
		UICanvas *pCanvas = dynamic_cast<UICanvas*>(pParent);
		if (pCanvas != nullptr)
		{
			m_pParentCanvas = pCanvas;
			return;
		}
	}
	m_pParentCanvas = nullptr;
	Utilities::Debug::LogWarning("UIObject only works when it is parrented to a UICanvas!\nThis object will not render properly!");
}

void UIObject::RootDraw(const GameContext& gameContext)
{
	if (!IsDirty()) return;

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

	SetDirty(false);

	Utilities::Debug::LogInfo("A UIObject was re-rendered!");
}
