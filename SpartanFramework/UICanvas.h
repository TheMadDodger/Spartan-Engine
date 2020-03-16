#pragma once
#include "GameObject.h"

class RenderTexture;

class UICanvas : public GameObject
{
public:
	UICanvas();
	virtual ~UICanvas();

private:
	void Initialize(const GameContext& gameContext) override;
	void Update(const GameContext& gameContext) override;
	void Draw(const GameContext& gameContext) override;
	void PostDraw(const GameContext& gameContext) override;

private:
	RenderTexture* m_pRenderTexture;
};

