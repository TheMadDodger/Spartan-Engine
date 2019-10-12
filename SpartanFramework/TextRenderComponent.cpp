#include "stdafx.h"
#include "TextRenderComponent.h"
#include "ContentManager.h"
#include "GameObject.h"
#include "TransformComponent.h"

TextRenderComponent::TextRenderComponent() : m_pFont(nullptr), m_Text("Hello World"), m_Origin(TopLeft), m_Color(1, 1, 1, 1), BaseComponent("Text")
{
}

TextRenderComponent::~TextRenderComponent()
{
	if (m_pTextTexture)
	{
		delete m_pTextTexture;
		m_pTextTexture = nullptr;
	}
}

void TextRenderComponent::SetText(const std::string &text)
{
	if (m_Text != text)
		m_IsDirty = true;

	m_Text = text;
}

void TextRenderComponent::SetAllignment(const Origin &allignment)
{
	if (m_Origin != allignment)
		m_IsDirty = true;

	m_Origin = allignment;
}

void TextRenderComponent::SetColor(const Color &col)
{
	if (m_Color != col)
		m_IsDirty = true;

	m_Color = col;
}

void TextRenderComponent::SetFont(FontData *pFont)
{
	if (m_pFont != pFont)
		m_IsDirty = true;

	m_pFont = pFont;
}

FontData *TextRenderComponent::GetFont()
{
	return m_pFont;
}

TextureData *TextRenderComponent::GetTextureData()
{
	return m_pTextTexture;
}

const std::string & TextRenderComponent::GetText()
{
	return m_Text;
}

const Color &TextRenderComponent::GetColor() const
{
	return m_Color;
}

void TextRenderComponent::SetMaxWidth(Uint32 maxWidth)
{
	if (m_MaxWidth != maxWidth)
		m_IsDirty = true;

	m_MaxWidth = maxWidth;
}

void TextRenderComponent::Initialize(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	auto pLoadedFont = ContentManager::GetInstance()->Load<FontData>(m_FontFile);
	if (!m_FontSet)
		m_pFont = pLoadedFont;

	m_IsDirty = true;
}

void TextRenderComponent::Draw(const GameContext &gameContext)
{
	SDL_Color color;
	color.r = Uint8(m_Color.r * 255);
	color.g = Uint8(m_Color.g * 255);
	color.b = Uint8(m_Color.b * 255);
	color.a = Uint8(m_Color.a * 255);
	if (m_IsDirty)
	{
		if (m_pTextTexture)
		{
			delete m_pTextTexture;
			m_pTextTexture = nullptr;
		}
		m_pTextTexture = gameContext.pRenderer->RenderText(m_pFont, m_Text, color, m_Origin, m_MaxWidth);
		m_IsDirty = false;
	}
	if (m_pTextTexture)
	{
		gameContext.pRenderer->RenderTexture(m_pTextTexture);
	}
}
