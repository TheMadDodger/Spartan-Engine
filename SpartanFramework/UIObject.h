#pragma once
#include "GameObject.h"

class UICanvas;

class UIObject : public GameObject
{
public:
	UIObject(const char* name = "UIObject", size_t layerID = 0);
	~UIObject();

	UICanvas* GetCanvas();

private:
	void OnParentUpdated(GameObject* pNewParent) override;
	virtual void RootDraw(const GameContext& gameContext) override;

protected:
	UICanvas* m_pParentCanvas;
};
