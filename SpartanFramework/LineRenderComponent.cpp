#include "stdafx.h"
#include "LineRenderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

namespace SpartanEngine
{
	LineRenderComponent::LineRenderComponent() : m_Color(1.0f, 1.0f, 1.0f, 1.0f)
	{
	}

	LineRenderComponent::~LineRenderComponent()
	{
	}

	void LineRenderComponent::SetColor(Color color)
	{
		m_Color = color;
	}

	void LineRenderComponent::SetStartAndEnd(Vector2 startPos, Vector2 endPos)
	{
		m_StartPos = startPos;
		m_EndPos = endPos;
	}

	void LineRenderComponent::Draw(const GameContext& gameContext)
	{
		gameContext.pRenderer->DrawLine(m_StartPos, m_EndPos, m_Color);
	}
}