#include "stdafx.h"
#include "LineRenderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "MaterialManager.h"

namespace SpartanEngine
{
	size_t LineRenderComponent::m_LineMatID = 0;
	UI::LineRenderMaterial* LineRenderComponent::m_pLineRenderer = nullptr;

	LineRenderComponent::LineRenderComponent() : m_Color(1.0f, 1.0f, 1.0f, 1.0f), UIComponent("Line"), m_LineWidth(1.0f)
	{
	}

	LineRenderComponent::~LineRenderComponent()
	{
	}

	void LineRenderComponent::SetColor(Color color)
	{
		m_Color = color;
		GetGameObject()->SetDirty();
	}

	void LineRenderComponent::SetStartAndEnd(Vector2 startPos, Vector2 endPos)
	{
		m_StartPos = startPos;
		m_EndPos = endPos;
		GetGameObject()->SetDirty();
	}

	void LineRenderComponent::SetLineWidth(float width)
	{
		m_LineWidth = width;
	}

	void LineRenderComponent::Initialize(const GameContext& gameContext)
	{
		CreateMaterial();
		SetCustomMaterial(m_pLineRenderer);
	}

	void LineRenderComponent::Draw(const GameContext& gameContext)
	{
		//gameContext.pRenderer->DrawLine(m_StartPos, m_EndPos, m_Color);
		m_pLineRenderer->SetStartAndEnd(m_StartPos, m_EndPos);
		m_pLineRenderer->SetUIColor(m_Color);
		m_pLineRenderer->SetLineWidth(m_LineWidth);
	}

	void LineRenderComponent::CreateMaterial()
	{
		if (m_pLineRenderer) return;
		m_LineMatID = MaterialManager::CreateMaterial<UI::LineRenderMaterial>("./Resources/Shaders/LineRenderer.fx");
		m_pLineRenderer = MaterialManager::GetMaterial<UI::LineRenderMaterial>(m_LineMatID);
	}
}