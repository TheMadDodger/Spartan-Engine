#pragma once
#include "GameObject.h"

class UICanvas;

class UIObject : public GameObject
{
	UIObject();
	~UIObject();

private:
	void OnParentUpdated(GameObject* pNewParent) override;

protected:
	UICanvas* m_pCanvas;
};
