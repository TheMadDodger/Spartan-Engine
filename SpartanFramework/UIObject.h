#pragma once
#include "GameObject.h"

class UICanvas;

class UIObject : public GameObject
{
public:
	UIObject(const char* name = "UIObject", size_t layerID = 0);
	~UIObject();

	UICanvas* GetCanvas();

//protected:
	//virtual void HandleMouse(const Vector2& relativeMousePos) override = 0;

private:
	void OnParentUpdated(GameObject* pNewParent) override;

protected:
	UICanvas* m_pParentCanvas;
};
