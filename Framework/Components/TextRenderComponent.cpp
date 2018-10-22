#include "stdafx.h"
#include "../../stdafx.h"
#include "TextRenderComponent.h"
#include "../Content/ContentManager.h"
#include "../Scenes/GameObject.h"
#include "TransformComponent.h"

TextRenderComponent::TextRenderComponent(const std::string &file) : m_FontFile(file), m_pFont(nullptr), m_Text("Hello World"), m_Origin(TopLeft), m_Color(1, 1, 1, 1)
{
}

TextRenderComponent::~TextRenderComponent()
{
}

void TextRenderComponent::SetText(const std::string &text)
{
	m_Text = text;
}

void TextRenderComponent::SetAllignment(const Origin &allignment)
{
	m_Origin = allignment;
}

void TextRenderComponent::SetColor(const Color & col)
{
	m_Color = col;
}

void TextRenderComponent::SetFont(FontData *pFont)
{
	m_pFont = pFont;
	m_FontSet = true;
}

void TextRenderComponent::Initialize(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	auto pLoadedFont = ContentManager::GetInstance()->Load<FontData>(m_FontFile);
	if (!m_FontSet)
		m_pFont = pLoadedFont;
}

void TextRenderComponent::Draw(const GameContext &gameContext)
{
	glPushMatrix();
	GetGameObject()->GetTransform()->ApplyTransform();
	SDL_Color color;
	color.r = Uint8(m_Color.r * 255);
	color.g = Uint8(m_Color.g * 255);
	color.b = Uint8(m_Color.b * 255);
	color.a = Uint8(m_Color.a * 255);
	gameContext.pRenderer->RenderText(m_pFont, m_Text, color, m_Origin);
	glPopMatrix();
}
