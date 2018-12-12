#include "stdafx.h"
#include "UIContainer.h"
#include "GameObject.h"
#include "Components.h"

UIContainer::UIContainer(const Vector2 &dimensions) : m_Dimensions(dimensions), m_Padding(Vector2::Zero()), m_Color({ 0.5f, 0.5f, 0.5f, 0.5f }), BaseComponent("UI Container")
{
}

UIContainer::~UIContainer()
{
	m_pUIPages.clear();
}

void UIContainer::SetPadding(const Vector2 &padding)
{
	m_Padding = padding;
}

void UIContainer::SetColor(const Color &color)
{
	m_Color = color;
}

void UIContainer::AddPage(GameObject *pPage)
{
	m_pUIPages.push_back(pPage);
}

void UIContainer::SetPage(size_t pageID)
{
	if (pageID < m_pUIPages.size())
		m_CurrentPage = pageID;

	for (auto pPage : m_pUIPages)
		pPage->SetEnabled(false);

	m_pUIPages[m_CurrentPage]->SetEnabled(true);
}

void UIContainer::Initialize(const GameContext &)
{
}

void UIContainer::Update(const GameContext &)
{
}

void UIContainer::Draw(const GameContext &gameContext)
{
	glPushMatrix();
	GetGameObject()->GetTransform()->ApplyTransform();
	gameContext.pRenderer->DrawSolidRect(m_Padding, m_Dimensions - m_Padding, m_Color);
	glPopMatrix();
}