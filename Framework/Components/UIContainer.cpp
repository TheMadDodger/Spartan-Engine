#include "stdafx.h"
#include "UIContainer.h"
#include "../Scenes/GameObject.h"
#include "Components.h"

UIContainer::UIContainer(const Vector2 &dimensions) : m_Dimensions(dimensions), m_Padding(Vector2::Zero()), m_Color({ 0.5f, 0.5f, 0.5f, 0.5f })
{
}

UIContainer::~UIContainer()
{
}

void UIContainer::SetPadding(const Vector2 &padding)
{
	m_Padding = padding;
}

void UIContainer::SetColor(const Color &color)
{
	m_Color = color;
}

void UIContainer::Initialize(const GameContext &gameContext)
{
}

void UIContainer::Update(const GameContext &gameContext)
{
}

void UIContainer::Draw(const GameContext &gameContext)
{
	glPushMatrix();
	GetGameObject()->GetTransform()->ApplyTransform();
	gameContext.pRenderer->DrawSolidRect(m_Padding, m_Dimensions - m_Padding, m_Color);
	glPopMatrix();
}
