#pragma once
#include "BaseComponent.h"

class LineRenderComponent : public BaseComponent
{
public:
	LineRenderComponent() {};
	LineRenderComponent(Vector2 startPos, Vector2 endPos);
	virtual ~LineRenderComponent();

	void SetColor(Color color);

	void SetStartAndEnd(Vector2 startPos, Vector2 endPos);

private:
	void Draw(const GameContext &gameContext) override;
	virtual BaseComponent *Create() { return new LineRenderComponent(); };

private:
	Vector2 m_StartPos;
	Vector2 m_EndPos;
	Color m_Color;
};

