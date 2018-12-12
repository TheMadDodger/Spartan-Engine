#include "stdafx.h"
#include "UIButton.h"
#include "InputManager.h"
#include "GameScene.h"
#include "Components.h"
#include "Framework.h"

UIButton::UIButton(TextureData *pIdleTexture, TextureData *pMouseOverTexture, TextureData *pMouseClicktexture, 
	TextureData *pSelectedTexture) :
	m_pIdleTexture(pIdleTexture), m_pMouseOverTexture(pMouseOverTexture), m_pClickTexture(pMouseClicktexture),
	m_pCurrentTexture(pIdleTexture), m_Size(m_pIdleTexture->GetDimensions()), m_pSelectedTexture(pSelectedTexture)
{
	SetTag("UIButton");
}

UIButton::UIButton() : m_Size(10.f, 10.f)
{
}

UIButton::~UIButton()
{
}

void UIButton::Select()
{
	m_Selected = true;
}

void UIButton::Unselect()
{
	m_Selected = false;
}

bool UIButton::IsMouseOver()
{
	return m_MouseOver;
}

bool UIButton::IsClicked()
{
	return m_MouseClicked;
}

void UIButton::SetClickBoxSize(const Vector2 &size)
{
	m_Size = size;
}

void UIButton::OnMouseOver()
{
}

void UIButton::OnMouseLeave()
{
}

void UIButton::OnMouseClick()
{
}

void UIButton::Initialize(const GameContext &)
{
	m_WasClickedThisFrame = false;

	AddComponent(new ImageRenderComponent(m_pCurrentTexture));
}

void UIButton::Update(const GameContext &gameContext)
{
	m_MouseClicked = false;
	auto mousePos = gameContext.pInput->GetMouseScreenPosition();

	auto pos = GetTransform()->GetWorldPosition();
	auto bottomRight = pos + m_Size;

	if (CheckPointInRect(mousePos, { GetTransform()->GetWorldPosition(), bottomRight }))
	{
		if (gameContext.pInput->IsMouseButtonDown(SDL_BUTTON_LEFT))
		{
			if (!m_WasClickedThisFrame)
			{
				m_MouseClicked = true;
				m_WasClickedThisFrame = true;
			}
		}
		else
		{
			m_WasClickedThisFrame = false;
			m_MouseClicked = false;
		}
		
		if (!m_MouseOver)
		{
			OnMouseOver();
		}
		m_MouseOver = true;
	}
	else
	{
		if (m_MouseOver)
		{
			OnMouseLeave();
		}
		m_MouseOver = false;
	}

	if (m_Selected)
	{
		m_pCurrentTexture = m_pSelectedTexture;
	}
	else if (m_MouseClicked)
	{
		m_pCurrentTexture = m_pClickTexture;
	}
	else if (m_MouseOver)
	{
		m_pCurrentTexture = m_pMouseOverTexture;
	}
	else
	{
		m_pCurrentTexture = m_pIdleTexture;
	}

	GetComponent<ImageRenderComponent>()->SetTexture(m_pCurrentTexture);
}

void UIButton::Draw(const GameContext &)
{
}