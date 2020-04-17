#include "stdafx.h"
#include "UIObject.h"
#include "UICanvas.h"
#include "Layers.h"

UIObject::UIObject() : m_pCanvas(nullptr), GameObject("UIObject")
{
}

UIObject::~UIObject()
{
}

void UIObject::OnParentUpdated(GameObject* pNewParent)
{
	GameObject* pParent = GetParent();
	while (pParent != nullptr)
	{
		UICanvas *pCanvas = dynamic_cast<UICanvas*>(pParent);
		if (pCanvas != nullptr)
		{
			m_pCanvas = pCanvas;
			return;
		}
	}
	m_pCanvas = nullptr;
	Utilities::Debug::LogWarning("UIObject only works when it is parrented to a UICanvas!\nThis object will not render properly!");
}
