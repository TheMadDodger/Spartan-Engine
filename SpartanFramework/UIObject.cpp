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
