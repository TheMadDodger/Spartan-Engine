#include "stdafx.h"
#include "TextRenderComponent.h"
#include "ContentManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "UIRenderMaterial.h"

namespace SpartanEngine
{
	TextRenderComponent::TextRenderComponent() : m_pFont(nullptr), m_Text("Hello World"), m_Color(1, 1, 1, 1), m_HasSetSize(false), UIComponent("Text")
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

	void TextRenderComponent::SetText(const std::string& text)
	{
		if (m_Text != text)
			GetGameObject()->SetDirty();

		m_Text = text;
	}

	void TextRenderComponent::SetColor(const Color& col)
	{
		if (m_Color != col)
			GetGameObject()->SetDirty();

		m_Color = col;
	}

	void TextRenderComponent::SetFont(FontData* pFont)
	{
		if (m_pFont != pFont)
			GetGameObject()->SetDirty();

		m_pFont = pFont;
	}

	FontData* TextRenderComponent::GetFont()
	{
		return m_pFont;
	}

	TextureData* TextRenderComponent::GetTextureData()
	{
		return m_pTextTexture;
	}

	const std::string& TextRenderComponent::GetText()
	{
		return m_Text;
	}

	const Color& TextRenderComponent::GetColor() const
	{
		return m_Color;
	}

	void TextRenderComponent::SetMaxWidth(Uint32 maxWidth)
	{
		if (m_MaxWidth != maxWidth)
			GetGameObject()->SetDirty();

		m_MaxWidth = maxWidth;
	}

	void TextRenderComponent::Draw(const GameContext& gameContext)
	{
		SDL_Color color;
		color.r = Uint8(m_Color.r * 255);
		color.g = Uint8(m_Color.g * 255);
		color.b = Uint8(m_Color.b * 255);
		color.a = Uint8(m_Color.a * 255);

		if (m_pTextTexture)
		{
			delete m_pTextTexture;
			m_pTextTexture = nullptr;
		}

		m_pTextTexture = gameContext.pRenderer->RenderText(m_pFont, m_Text, color, GetOrigin(), m_MaxWidth);

		if (!m_HasSetSize)
		{
			GetGameObject()->SetSize(m_pTextTexture->GetDimensions().x, m_pTextTexture->GetDimensions().y);
			m_HasSetSize = true;
		}

		if (m_pTextTexture == nullptr) return;
		m_pUIRenderer->SetUITexture(m_pTextTexture);

		Vector4 offsets = Math::CalculateOffsets(GetOrigin(), GetGameObject()->GetSize());
		m_pUIRenderer->SetOffsets(offsets);
	}
}