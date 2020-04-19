#pragma once
#include "BaseComponent.h"
#include "UIObject.h"

class UIRenderMaterial;

class UIComponent : public BaseComponent
{
public:
	UIComponent(const char* name);
	~UIComponent();

	UIObject* GetGameObject();

protected:
	virtual void RootUpdate(const GameContext& gameContext) override;
	virtual void RootDraw(const GameContext& gameContext) override;

private:
	void Render();

protected:
	UIRenderMaterial* m_pUIRenderer;

private:
	Matrix4X4 m_UIMatrix;
	static size_t m_UIVertexBufferID;
	static bool m_DoesVertexBufferExist;
	static int m_InstanceCount;
};
